
#### Making network requests

```xml
<dependency>
  <groupId>com.fasterxml.jackson.core</groupId>
  <artifactId>jackson-databind</artifactId>
  <version>2.18.0</version>
</dependency>
```

```gradle
dependencies {
    implementation 'com.fasterxml.jackson.core:jackson-core:2.13.3'
    implementation 'com.fasterxml.jackson.core:jackson-annotations:2.13.3'
    implementation 'com.fasterxml.jackson.core:jackson-databind:2.13.3'
}
```

```java
public record Todo (
  long userId,
  long id,
  String title,
  boolean completed
) {}
```

```java
import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.URISyntaxException;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Duration;
import com.fasterxml.jackson.databind.ObjectMapper;

public class TodoRespository {
  private final String baseURL = "https://jsonplaceholder.typicode.com/todos/";
  private ObjectMapper mapper = new ObjectMapper();
  private HttpClient client = HttpClient.newHttpClient();

  public Todo getTodoById(long id) throws Exception {
    URI uri = new URI(baseURL + id);

    HttpRequest req = HttpRequest.newBuilder()
        .uri(uri)
        .GET()
        .timeout(Duration.ofSeconds(10))
        .header("Content-Type", "application/json")
        .build();

    HttpResponse<String> res = client.send(req, HttpResponse.BodyHandlers.ofString());
    return mapper.readValue(res.body(), Todo.class);
  }
}
```

```java
import java.io.IOException;
import java.net.URISyntaxException;

public class Main {
	public static void main(String[] args) {
		TodoRespository repo = new TodoRespository();
		try {
			Todo todo = repo.getTodoById(1);
			System.out.println(todo);
		} catch (Exception ex) {
			System.out.printf("error: %s\n", ex.getMessage());
		}
	}
}
```


---

#### Downloading files

```java
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