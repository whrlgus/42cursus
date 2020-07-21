FROM debian:buster
COPY srcs tmp

# Install LEMP Stack and others
RUN apt update && apt install -y \
	nginx \
	mariadb-server \
	php7.3-fpm php7.3-mysql \	
	openssl \
	wget

# Create ssl certificate and set nginx server blocks
RUN openssl req \
       -newkey rsa:2048 -nodes -keyout /etc/ssl/private/localhost.key \
       -x509 -out /etc/ssl/certs/localhost.crt \
       -subj '/C=KR'
RUN mv /tmp/default /etc/nginx/sites-available/default

# Install wordpress and set configuration
RUN wget https://wordpress.org/latest.tar.gz && \
	tar -xvf latest.tar.gz -C /var/www/html/ && \
	rm latest.tar.gz && \
	mv /tmp/wp-config.php /var/www/html/wordpress/
RUN service mysql start && mysql -u root < /tmp/wordpress_setup.sql

# Install phpmyadmin and set configuration
RUN wget https://files.phpmyadmin.net/phpMyAdmin/4.9.5/phpMyAdmin-4.9.5-all-languages.tar.gz && \
	tar -xvf phpMyAdmin-4.9.5-all-languages.tar.gz && \
	mv phpMyAdmin-4.9.5-all-languages /var/www/html/phpmyadmin && \
	mv /tmp/config.inc.php /var/www/html/phpmyadmin/

ENTRYPOINT ["/bin/bash","/tmp/entrypoint.sh"]
