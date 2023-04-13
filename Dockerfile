FROM docker.io/php:apache
ARG BUILD_TYPE=production

RUN docker-php-ext-install mysqli && docker-php-ext-enable mysqli
# Use the default production configuration
RUN mv "$PHP_INI_DIR/php.ini-$BUILD_TYPE" "$PHP_INI_DIR/php.ini"
RUN printf 'PassEnv hfsHost\nPassEnv hfsDB\nPassEnv hfsDBuser\nPassEnv hfsDBpw\n' >  /etc/apache2/conf-available/hfs.conf && a2enconf hfs

COPY . /var/www/html/
