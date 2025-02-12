In order to link a domain to a server IP, the following records need to be created.

```
Type: A 
Content: <Server IPv4 Address> (e.g. 85.211.5.68)
Name: @ (optional)
Priority: 0 (optional)
TTL: 14400 (optional)
```

```
Type: CNAME 
Content: <Domain without 'www'> (e.g. mysite.com)
Name: www (optional)
Priority: 0 (optional)
TTL: 14400 (optional)
```

```
Type: AAAA (optional)
Content: <Server IPv6 Address> (e.g. 2a02:4780:10:58d8::1)
Name: @ (optional)
Priority: 0 (optional)
TTL: 18000 (optional)
```

**Note**: The above `AAAA` record is optional and only required if the server's IPv6
address is available. In order to find the IPv6 address of the server, run the following command 
on the server (pick the global IPv6 address).

```bash
$ ip -6 addr
```
