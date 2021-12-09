# Cloud Deployment Guide

We are going to be deploying our application to [heroku](https://heroku.com), a simple PaaS system.

To do so, you will need to follow these steps:

## Step 1 : Create a Heroku Account

Please sign up for a heroku account and install the heroku command line tools.  You may use whatever 
email you'd like to sign up.

## Step 2 : Create a Heroku Application

Once you have set up a heroku account and gotten the `heroku` command line tool working, you should
be able to create an application on the heroku platform:

```bash
  $ heroku create <your-name>-archive-cat
```

where you subsitute something for `<your-name>` (e.g. `cgross-archive-cat`).  This is the unique
name of the cloud application for your version of ArchiveCat.

## Step 3: Update ArchiveCat to understand the `PORT` environment variable

Update the code in `Server.java` to use an environment variable for which port it runs on, to make
it compatible with Heroku:

```java
    public static void main(String[] args) {

        port(getPort());
    ...
    }
      
      
    protected static int getPort() {
        ProcessBuilder processBuilder = new ProcessBuilder();
        if (processBuilder.environment().get("PORT") != null) {
            return Integer.parseInt(processBuilder.environment().get("PORT"));
        }
        return 8001;
    }
```

## Step 4: Update Your pom.xml file To Include the Heroku Build Plugins:

Add this `<build>` tag to your pom.xml file.  Be sure to update the `<appName>` tag to be the
app name you picked in Step 2!

```xml
    <build>
        <finalName>ArchiveCat</finalName>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <version>3.8.0</version>
                <configuration>
                    <source>11</source>
                    <target>11</target>
                </configuration>
            </plugin>
            <plugin>
                <groupId>com.heroku.sdk</groupId>
                <artifactId>heroku-maven-plugin</artifactId>
                <version>3.0.4</version>
                <configuration>
                    <jdkVersion>11</jdkVersion>
                    <!-- Use your own application name -->
                    <appName>cgross-archive-cat</appName>
                    <processTypes>
                        <!-- Tell Heroku how to launch your application -->
                        <!-- You might have to remove the ./ in front   -->
                        <web>java -jar ./target/ArchiveCat-jar-with-dependencies.jar</web>
                    </processTypes>
                </configuration>
            </plugin>
            <plugin>
                <artifactId>maven-assembly-plugin</artifactId>
                <executions>
                    <execution>
                        <phase>package</phase>
                        <goals>
                            <goal>single</goal>
                        </goals>
                    </execution>
                </executions>
                <configuration>
                    <descriptorRefs>
                        <!-- This tells Maven to include all dependencies -->
                        <descriptorRef>jar-with-dependencies</descriptorRef>
                    </descriptorRefs>
                    <archive>
                        <manifest>
                            <mainClass>edu.montana.csci.csci366.archivecat.Server</mainClass>
                        </manifest>
                    </archive>
                </configuration>
            </plugin>
        </plugins>
    </build>
```

## Step 5: Deploy your application

You should now be able to deploy your web application to the cloud with the following maven command, run
in the root directory of the cloud app:

```bash
  $ mvn heroku:deploy -DskipTests
```
