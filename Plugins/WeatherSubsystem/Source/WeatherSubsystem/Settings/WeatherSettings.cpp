// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherSettings.h"


UWeatherSettings::UWeatherSettings()
{

    // Clear the array before adding default values
    Seasons.Empty();


    FSeasonConfig Winter;
        Winter.SeasonName = TEXT("Winter");
        Winter.bEnabled = true;
        Seasons.Add(Winter);

    FSeasonConfig Spring;
        Spring.SeasonName = TEXT("Spring");
        Spring.bEnabled = true;
        Seasons.Add(Spring);

    FSeasonConfig Summer;
        Summer.SeasonName = TEXT("Summer");
        Summer.bEnabled = true;
        Seasons.Add(Summer);

    FSeasonConfig Fall;
        Fall.SeasonName = TEXT("Fall");
        Fall.bEnabled = true;
        Seasons.Add(Fall);
}