```java
public class EmailService {
  private static EmailService instance;
  private String format;

  private EmailService() {
    this.format = "Sending email to '%s' with content '%s'\n";
  }

  // this method returns string only for testing purposes
  public String sendMail(String to, String message) {
    return String.format(this.format, to, message);
  }

  public static EmailService getInstance() {
    if (EmailService.instance == null) {
      EmailService.instance = new EmailService();
    }

    return EmailService.instance;
  }
}
```

```java
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.Test;

public class EmailServiceTest {
  @Test
  public void testGetInstance() {
    assertNotEquals(EmailService.getInstance(), null);
  }

  @Test
  public void testSendEmail() {
    String to = "admin@site.com";
    String content = "Some message";

    String result = EmailService.getInstance().sendMail(to, content);
    assertTrue(result.contains(to));
    assertTrue(result.contains(content));
  }
}
```
