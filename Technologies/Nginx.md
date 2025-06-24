#### Using as reverse proxy

Consider the scenario where your web application has an integrated server which 
runs on a port other than port `80`. Remember that the default exposed port for 
a web server is `80` and the website should be served through this port. However,
this port can only be used by root and it is never recommended that our server
process should be executed as root. 

The solution is to use Nginx as a reverse proxy which will map the port of our 
application server (e.g. `3000`) onto port `80`.

---

##### The config file

Assuming that we a setting up Nginx for domain `mysite.com`, we will create the 
following file `/etc/nginx/sites-available/mysite.com` and also create a symlink
at `/etc/nginx/sites-enabled/mysite.com`. The content will be as follows.

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
}
```

**Note**: The above code assumes that the application port is `3000`.


---

##### Applying changes

Any time we modify the nginx config files we can verify the the configs are 
correct by running the following command.

```bash
$ sudo nginx -t
```

If everything is ok, we can restart the nginx systemd service.

```bash
$ sudo systemctl restart nginx
```