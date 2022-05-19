#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum scales{Celsius = 1, Fahrenheit = 2, Kelvin = 3};

int identifyScale(char inputScale[]) {
    int numberOfScales;
    enum scales scale = 0;

    char *celsius[] = {"°C", "c", "C", "celsius", "Celsius"};
    numberOfScales = sizeof(celsius)/sizeof(celsius[1]);
    for (int i = 0; i < numberOfScales; i++) {
        if (strcmp(inputScale, celsius[i]) == 0)
            scale = Celsius;
    }

    char *fahrenheit[] = {"°F", "f", "F", "fahrenheit", "Fahrenheit"};
    numberOfScales = sizeof(fahrenheit)/sizeof(fahrenheit[1]);
    for (int i = 0; i < numberOfScales; i++) {
        if (strcmp(inputScale, fahrenheit[i]) == 0)
            scale = Fahrenheit;
    }

    char *kelvin[] = {"k", "K", "kelvin", "Kelvin"};
    numberOfScales = sizeof(kelvin)/sizeof(kelvin[1]);
    for (int i = 0; i < numberOfScales; i++) {
        if (strcmp(inputScale, kelvin[i]) == 0)
            scale = Kelvin;
    }

    return scale;
}

bool isKnownScale(char inputScale[]) {
    if (identifyScale(inputScale) != 0)
        return true;
    else
        return false;
}

float celsiusToFahrenheit(float temperatureInCelsius){
    return (temperatureInCelsius * 9 / 5) + 32;
}

float celsiusToKelvin(float temperatureInCelsius){
    return temperatureInCelsius + 273.15;
}

float fahrenheitToCelsius(float temperatureInFahrenheit){
    return (temperatureInFahrenheit - 32) * 5 / 9;
}

float fahrenheitToKelvin(float temperatureInFahrenheit){
    return 273.5 + ((temperatureInFahrenheit - 32.0) * (5.0/9.0));
}

float kelvinToCelsius(float temperatureInKelvin){
    return temperatureInKelvin - 273.15;
}

float kelvinToFahrenheit(float temperatureInKelvin){
    return (temperatureInKelvin - 273.15) * 9/5 + 32; 
}

typedef enum {
    celsiusFahrenheit = 12,
    celsiusKelvin = 13,
    fahrenheitCelsius = 21,
    fahrenheitKelvin = 23,
    kelvinCelsius = 31,
    kelvinFahrenheit = 32
}Modes;

void converter(float inputTemperature, Modes mode) {
    switch (mode) {
    case celsiusFahrenheit:
        printf("%.2f\n", celsiusToFahrenheit(inputTemperature));
        break;
    case celsiusKelvin:
        printf("%.2f\n", celsiusToKelvin(inputTemperature));
        break;
    case fahrenheitCelsius:
        printf("%.2f\n", fahrenheitToCelsius(inputTemperature));
        break;
    case fahrenheitKelvin:
        printf("%.2f\n", fahrenheitToKelvin(inputTemperature));
        break;
    case kelvinCelsius:
        printf("%.2f\n", kelvinToCelsius(inputTemperature));
        break;
    case kelvinFahrenheit:
        printf("%.2f\n", kelvinToFahrenheit(inputTemperature));
        break;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        puts("temp_convert: error: Not enough arguments.");
        puts("Usage: temp_convert INPUT_SCALE OUTPUT_SCALE [TEMPERATURE]...");
        return EXIT_FAILURE;
    }
    else {
        if (isKnownScale(argv[1]) == true) {
            int mode = identifyScale(argv[1]) * 10;
            if (isKnownScale(argv[2]) == true) {
                mode += identifyScale(argv[2]);
                if ( argc == 3)
                    puts("");
                for (int i = 3; i < argc; i++) {
                    float inputTemperature = atof(argv[i]);
                    converter(inputTemperature, mode);
                }
                return EXIT_SUCCESS;
            } else {
                printf("temp_convert: error: Unrecognized temperature scale %s\n",argv[2]);
                return EXIT_FAILURE;
            }
        } else {
            printf("temp_convert: error: Unrecognized temperature scale %s\n",argv[1]);
            return EXIT_FAILURE;
        }
    }
}