import requests

KM_CONSTANT = 1.609


def get_distance(this_city, this_state, other_city, other_state) -> float:
    """
    Gets the distance between one city and another city
    :param this_city: name of first city
    :param this_state: state/province of first city (ex. "Ohio" can be typed full name or abbreviated "OH")
    :param other_city: name of second city
    :param other_state: state/province of second city (ex. "Ohio" can be typed full name or abbreviated "OH")
    :return: the distance (in miles) between the two cities
    """
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
        return float("inf")


"""
________________________________

    PRIVATE HELPER METHODS

________________________________

"""


def __get_city_data(city, state) -> dict:
    """
    Gets city data from Mapquest
    :param city: a city
    :param state: the state/province of the city
    :return: a dictionary containing teh city's geographical information
    """
    api_key = "vlZBd7FQnVdBaNgArEYdFMm8q60Imnyu"
    request_url = "https://www.mapquestapi.com/geocoding/v1/address?key=" + api_key + "&location=" \
                  + city + "," + state
    response = requests.get(request_url)
    if response.status_code == 200:  # HTTP response code successful
        data = response.json()
        return data
    else:
        print("Error: " + str(response.status_code))
        return {}


def __get_city(data) -> str:
    """
    :param data: Mapquest Dictionary of a city's data (from __get_city_data())
    :return: the city according to Mapquest
    """
    return data["results"][0]["locations"][0]["adminArea5"]


def __get_state(data) -> str:
    """
    :param data: Mapquest Dictionary of a city's data (from __get_city_data())
    :return: the state according to Mapquest data
    """
    return data["results"][0]["locations"][0]["adminArea3"]


def __get_postal_code(data) -> int:
    """
    :param data: Mapquest Dictionary of a city's data (from __get_city_data())
    :return: the postal code according to Mapquest data
    """
    return data["results"][0]["locations"][0]["postalCode"]


def __get_country(data) -> str:
    """
    :param data: Mapquest Dictionary of a city's data (from __get_city_data())
    :return: the country according to Mapquest data
    """
    return data["results"][0]["locations"][0]["adminArea1"]


def __get_longitude(data) -> float:
    """
    :param data: Mapquest Dictionary of a city's data (from __get_city_data())
    :return: the longitude of the city
    """
    return data["results"][0]["locations"][0]["latLng"]["lng"]


def __get_latitude(data) -> float:
    """
    :param data: Mapquest Dictionary of a city's data (from __get_city_data())
    :return: the latitude
    """
    return data["results"][0]["locations"][0]["latLng"]["lat"]


def __lat_long_str(data) -> str:
    """
    :param data: Mapquest Dictionary of a city's data (from __get_city_data())
    :return: the latitude and longitude as a string, in the form: "lat,lng"
    """
    return str(__get_latitude(data)) + "," + str(__get_longitude(data))
