The following dependency is required before environment variables can be read in the application.

```xml
<dependency>
	<groupId>me.paulschwarz</groupId>
	<artifactId>spring-dotenv</artifactId>
	<version>4.0.0</version>
</dependency>
```

The `.env` file will be located at the root of the project (i.e. next to the `pom.xml`file).


---

#### Example

Let's say we have the following variables in our `.env` file.

```
HOSTAWAY_ACCOUNT_ID=xxxx
HOSTAWAY_API_KEY=xxxxx
HOSTAWAY_ACCESS_TOKEN=xxxxx
```

We can embed the environment variable values inside our `resources/application.properties` file.

```properties
hostaway.accountId=${HOSTAWAY_ACCOUNT_ID}
hostaway.apiKey=${HOSTAWAY_API_KEY}
hostaway.accessToken=${HOSTAWAY_ACCESS_TOKEN}
```

Next, we will need a class to hold all these variables, as read from the properties file.

```java
import org.springframework.stereotype.Component;
import org.springframework.boot.context.properties.ConfigurationProperties;

@Component
@ConfigurationProperties(prefix = "hostaway")
public class HostawayConfig {
    private String accountId;
    private String apiKey;
    private String accessToken;

    public String getAccountId() {
        return accountId;
    }

    public String getApiKey() {
        return apiKey;
    }

    public String getAccessToken() {
        return accessToken;
    }

    public void setAccountId(String accountId) {
        this.accountId = accountId;
    }

    public void setApiKey(String apiKey) {
        this.apiKey = apiKey;
    }

    public void setAccessToken(String accessToken) {
        this.accessToken = accessToken;
    }
}
```