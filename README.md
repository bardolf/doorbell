# Doorbell




## Build

### Server

Build and publish

```shell
docker build . -t bardolf/doorbell:0.9.2
docker tag bardolf/doorbell:0.9.2 bardolf/doorbell:0.9.2
docker push  bardolf/doorbell:0.9.2
```

### ESP32




## Installation

We run the app as a docker 

```shell
docker run -d -p 3000:3000 -p 3010:3010 --name doorbell bardolf/doorbell:0.9.2
```

Nginx setup could look like 

```nginx
server {
        listen 443;
        server_name doorbell.skybit.cz;

        ssl_certificate           /etc/letsencrypt/live/skybit.cz/fullchain.pem;
        ssl_certificate_key       /etc/letsencrypt/live/skybit.cz/privkey.pem;

        ssl on;
        ssl_session_cache  builtin:1000  shared:SSL:10m;
        ssl_protocols  TLSv1.1 TLSv1.2;
        ssl_ciphers 'ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-AES256-GCM-SHA384:DHE-RSA-AES128-GCM-SHA256:DHE-DSS-AES128-GCM-SHA256:kEDH+AESGCM:ECDHE-RSA-AES128-SHA256:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA:ECDHE-ECDSA-AES128-SHA:ECDHE-RSA-AES256-SHA384:ECDHE-ECDSA-AES256-SHA384:ECDHE-RSA-AES256-SHA:ECDHE-ECDSA-AES256-SHA:DHE-RSA-AES128-SHA256:DHE-RSA-AES128-SHA:DHE-DSS-AES128-SHA256:DHE-RSA-AES256-SHA256:DHE-DSS-AES256-SHA:DHE-RSA-AES256-SHA';

        ssl_prefer_server_ciphers on;

        access_log            /var/log/nginx/doorbell.skybit.cz.access.log;

        location /ws {
            proxy_pass         http://localhost:3010;
            proxy_http_version 1.1;
            proxy_set_header Upgrade $http_upgrade;
            proxy_set_header Connection "Upgrade";
            proxy_set_header Host $host;
        }

        location / {
                proxy_pass              http://127.0.0.1:3000;
                proxy_set_header        Host $host;
                proxy_set_header        X-Real-IP $remote_addr;
                proxy_set_header        X-Forwarded-For $proxy_add_x_forwarded_for;
                proxy_set_header        X-Forwarded-Proto $scheme;                
                proxy_read_timeout  90;
        }
}
```

