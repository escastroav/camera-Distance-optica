#!/bin/bash

FOLDER1="images_gimp/led_init/";
FOLDER2="images_gimp/led_15mm/";
FOLDER3="images_gimp/laser_conf_default/";
FOLDER4="images_gimp/laser_config_2/";

MATRIX="";
IMAGE="";
IMAGE1="g_a_1";
IMAGE2="g_a_2";

TRY1="laser_intento_1.bmp ";
TRY2="laser_intento_2.bmp ";

echo -e "prueba incertidumbre led";
echo -e "x\t""y";

for i in `seq 1 10`;
do
    echo -e "led init "$i
    IMAGE=$FOLDER1"g_led"$i".bmp ";
    ./measure.x $IMAGE;
    echo -e "led final "$i
    IMAGE=$FOLDER2"g_led"$i"final.bmp ";
    ./measure.x $IMAGE;
done;

echo -e "laser intento 1 led";
echo -e "0-1\t""0-2";

IMAGE=$FOLDER3"g_a_0_"$TRY1;
IMAGE1=$FOLDER3"g_a_1_"$TRY1;
IMAGE2=$FOLDER3"g_a_2_"$TRY1;
./measure.x $IMAGE $IMAGE1 $IMAGE2; 

echo -e "laser intento 2 led";

IMAGE=$FOLDER4"g_a_0_"$TRY2;
IMAGE1=$FOLDER4"g_a_1_"$TRY2;
IMAGE2=$FOLDER4"g_a_2_"$TRY2;
./measure.x $IMAGE $IMAGE1 $IMAGE2; 


