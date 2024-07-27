
#### Making network requests

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
import java.net.URISyntaxException;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Duration;
import com.fasterxml.jackson.databind.ObjectMapper;

public class TodoRespository {
  ObjectMapper mapper = new ObjectMapper();
  private final String baseURL = "https://jsonplaceholder.typicode.com/todos/%d";

  public Todo getTodoById(long id)
      throws URISyntaxException, IOException, InterruptedException {
    URI uri = new URI(String.format(baseURL, id));

    HttpRequest req = HttpRequest.newBuilder()
        .uri(uri)
        .GET()
        .timeout(Duration.ofSeconds(10))
        .build();

    HttpResponse<String> res = HttpClient.newBuilder()
        .build()
        .send(req, HttpResponse.BodyHandlers.ofString());

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
		} catch (URISyntaxException uriEx) {
			System.out.printf("error: %s\n", uriEx.getMessage());
		} catch (IOException ioEx) {
			System.out.printf("error: %s\n", ioEx.getMessage());
		} catch (InterruptedException intEx) {
			System.out.printf("error: %s\n", intEx.getMessage());
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