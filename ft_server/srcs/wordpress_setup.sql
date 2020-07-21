CREATE DATABASE wordpress;
GRANT ALL PRIVILEGES ON wordpress.* TO 'root'@'localhost' WITH GRANT OPTION;
UPDATE mysql.user SET plugin='mysql_native_password' WHERE user='root';
FLUSH PRIVILEGES;
