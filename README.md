# Doorbell


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

