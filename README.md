# Doorbell




## Build

### Server

Build and publish

```shell
docker build . -t bardolf/doorbell:0.9.2
docker tag bardolf/doorbell:0.9.2 bardolf/doorbell:0.9.2
docker push  bardolf/doorbell:0.9.2
```

run

```shell
docker run -d -p 3000:3000 -p 3010:3010 --name doorbell bardolf/doorbell:0.9.2
```

### ESP32




## Installation

We use xinetd service, we could also write simple server

```shell
$ cat /etc/xinetd.d doorbell

service doorbell
{
  disable = no
  server = /home/milan/projects/doorbell/doorbell.sh
  socket_type = stream
  protocol = tcp
  user = milan
  type = unlisted
  wait = no
  port = 9432
}
```

The doorbell.sh does the visualization part.

