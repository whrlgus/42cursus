#!/bin/sh

rm /tmp/*
service nginx start
service mysql start
service php7.3-fpm start
bash

