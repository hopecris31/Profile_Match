import requests

KM_CONSTANT = 1.609


def get_distance(this_city, this_state, other_city, other_state):
    this_data = __get_city_data(this_city, this_state)
    other_data = __get_city_data(other_city, other_state)

    this_coordinates = __lat_long_str(this_data)
    other_coordinates = __lat_long_str(other_data)

    api_key = "vlZBd7FQnVdBaNgArEYdFMm8q60Imnyu"
    endpoint = "https://www.mapquestapi.com/directions/v2/routematrix"

    response = requests.get(endpoint, {'key': api_key, 'from': this_coordinates, 'to': other_coordinates})

    if response.status_code == 200:
        data = response.json()
        distance = data['distance'][1]
        return distance
    else:
        print("Error: " + str(response.status_code) + ":" + str(response.text))
        return None


"""
________________________________

    PRIVATE HELPER METHODS

________________________________

"""


def __get_city_data(city, state):
    api_key = "vlZBd7FQnVdBaNgArEYdFMm8q60Imnyu"
    request_url = "https://www.mapquestapi.com/geocoding/v1/address?key=" + api_key + "&location=" \
                  + city + "," + state
    response = requests.get(request_url)
    if response.status_code == 200:  # HTTP response code successful
        data = response.json()
        return data
    else:
        print("Error: " + str(response.status_code))
        return None


def __get_city(data):
    return data["results"][0]["locations"][0]["adminArea5"]


def __get_state(data):
    return data["results"][0]["locations"][0]["adminArea3"]


def __get_postal_code(data):
    return data["results"][0]["locations"][0]["postalCode"]


def __get_country(data):
    return data["results"][0]["locations"][0]["adminArea1"]


def __get_longitude(data):
    return data["results"][0]["locations"][0]["latLng"]["lng"]


def __get_latitude(data):
    return data["results"][0]["locations"][0]["latLng"]["lat"]


def __lat_long_str(data):
    return str(__get_latitude(data)) + "," + str(__get_longitude(data))
