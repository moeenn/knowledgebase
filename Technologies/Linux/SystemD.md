#### Create custom service

The configuration file for the service is located at `/etc/systemd/system/<service-name>.service`.

Following are the sample content for a web application binary which needs to auto-run
the the background (restarted if needed).

```
[Unit]
Description=<service-name>
After=network.target

[Service]
ExecStart=<path/to/binary/or/script>
WorkingDirectory=</path/to/directory/containing/binary/or/script>
Type=simple
Restart=always

[Install]
WantedBy=default.target
```