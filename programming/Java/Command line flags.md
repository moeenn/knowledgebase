
```xml
<dependency>
  <groupId>commons-cli</groupId>
  <artifactId>commons-cli</artifactId>
  <version>1.9.0</version>
</dependency>
```


```java
package com.sandbox;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.DefaultParser;
import org.apache.commons.cli.Options;

public class Main {
    private static class CommandLineArgs {
        private final boolean version;
        private final String file;

        private final String FILE_FLAG = "file";
        private final String VERSION_FLAG = "version";

        public CommandLineArgs(String[] args) throws Exception {
            final Options options = new Options();
            options.addOption(VERSION_FLAG, false, "Version of the progam");
            options.addOption(FILE_FLAG, true, "File to process");

            CommandLineParser parser = new DefaultParser();
            CommandLine line = parser.parse(options, args);

            version = (line.hasOption(VERSION_FLAG));

            if (!line.hasOption(FILE_FLAG)) {
                throw new Exception("file argument is required");
            }

            file = line.getOptionValue(FILE_FLAG);
        }

        public boolean isVersion() {
            return version;
        }

        public String getFile() {
            return file;
        }

        @Override
        public String toString() {
            return "CommandLineArgs [version=" + version + ", file=" + file + "]";
        }
    }

    public static void main(String[] args) {
        CommandLineArgs commandLineArgs;
        try {
            commandLineArgs = new CommandLineArgs(args);
        } catch (Exception e) {
            System.err.println("error: " + e.getMessage());
            return;
        }

        System.out.println(commandLineArgs);
    }
}
```