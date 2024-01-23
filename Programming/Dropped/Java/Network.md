#### Download Files

```java
package com.sandbox.downloader;

import java.net.URL;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;
import java.io.FileOutputStream;
import java.io.IOException;

public class Downloader {
  public static void downloadFile(String url, String filename) throws IOException {
    ReadableByteChannel channel = Channels.newChannel(new URL(url).openStream());
    FileOutputStream fileStream = new FileOutputStream(filename);
    
    fileStream
      .getChannel()
      .transferFrom(channel, 0, Long.MAX_VALUE);

    fileStream.close();
  }
}
```

