
#### Docker config

```yml
services:
  nginx:
    image: nginx:1.29.1-alpine
    ports:
      - "8080:80"  # Map container port 80 to host port 8080.
    volumes:
      - ./nginx.conf:/etc/nginx/nginx.conf:ro
      - ./html:/usr/share/nginx/html:ro # Mount static content
    restart: unless-stopped
```


---

#### Using as reverse proxy

Consider the scenario where your web application has an integrated server which 
runs on a port other than port `80`. Remember that the default exposed port for 
a web server is `80` and the website should be served through this port. However,
this port can only be used by root and it is never recommended that our server
process should be executed as root. 

The solution is to use `nginx` as a reverse proxy which will map the port of our 
application server (e.g. `3000`) onto port `80`.


---

#### Serving static files

```
events {
    worker_connections 1024;
}

http {
    include /etc/nginx/mime.types;
    default_type application/octet-stream;

    # enable compression.
    gzip on;
    gzip_types text/css application/javascript text/xml;
    gzip_proxied any;

    # enable caching.
    proxy_cache_path /var/cache/nginx levels=1:2 keys_zone=my_cache:10m max_size=1g inactive=60m use_temp_path=off;

    server {
        listen 80;
        server_name localhost; # i.e. domain-name.com

        location / {
            root /usr/share/nginx/html;
            # index index.html index.htm;
            try_files $uri $uri/ =404;

            # cache settings.
            proxy_cache my_cache;
            proxy_cache_valid 200 1h;  # Cache 200 responses for 1 hour

            # cache headers.
            expires 1M;
            access_log off;
            add_header Cache-Control "max-age=2629746, public"; # in seconds.
        }
    }
}
```


---

##### The config file

Assuming that we a setting up `nginx` for domain `mysite.com`, we will create the 
following file `/etc/nginx/sites-available/mysite.com` and also create a symlink
at `/etc/nginx/sites-enabled/mysite.com`. The content will be as follows.


###### Basic config 

```
server{
    server_name mysite.com;
    location / {
        proxy_pass http://127.0.0.1:3000;
    }
}
```


###### More involved example 

```
server{
    server_name mysite.com;
    location / {
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header Host $host;
        proxy_pass http://127.0.0.1:3000;
        proxy_http_version 1.1;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection "upgrade";
    }
    
    gzip on;
    gzip_types text/css application/javascript image/png image/jpeg image/webp;
    gzip_proxied any;
}
```

**Note**: The above code assumes that the application port is `3000`.


---

##### Applying changes

Any time we modify the `nginx` config files we can verify the the configs are 
correct by running the following command.

```bash
# check if all configs are ok.
$ sudo nginx -t

# reload configs.
$ sudo ngingx -s reload

# optional.
$ sudo systemctl restart nginx
```

