# CSCI 366 - ArchiveCat

## Overview

This is the Cloud project for CSCI 366 - Systems.  It is designed to give you an introduction to cloud development and working with the web.

The goal of this project is to build a web archiver, a simplified version of [The Wayback Machine](https://archive.org/),
a system that allows you to capture a webpage and *archive* it to a copy, with all the supporting resources necessary
for rendering that page (images, style sheets, any javascript.)

## Your Tasks

Since this is not a web programming class, I will be giving you most of the infrastructure for the web application.  You
will have three components that you need to implement:

1. The `edu.montana.csci.csci366.archivecat.archiver.Archiver.archive()` method, which downloads and parses a webpage 
   using the [Jsoup](https://jsoup.org/) library

2. The job definitions in `edu.montana.csci.csci366.archivecat.archiver.jobs`, which correspond to the types of support
   resources that need to be downloaded and saved alongside the webpage downloaded above.  Each job will need to implement
   the following methods:
     * `downloadResource()` - this method downloads the resource from a remote site for local archiving.  It should use
       the URL of the element it is updating (e.g. a CSS tag) to get the remote URL, and then download it using the
       [HttpClient](https://docs.oracle.com/en/java/javase/11/docs/api/java.net.http/java/net/http/HttpClient.html) class 
       provided by java.  For the name of the local file, I recommend using the `Archive.computeSHA1()` method, and
       for saving the file, the `Archive.saveFile()` method.
     * `updateElement()` - this method updates the Element associated with the job, rewiring the original URL which was
       downloaded to the URL of the downloaded file.
     * `getURL()` - this method gets the original URL of the resource from the Element associated with the job.  You
       should use the `abs:` prefix when getting the URL out of an attribute, to get the absolute URL of the resource.

3. The job runners in `edu.montana.csci.csci366.archivecat.archiver.runners`, which run the download jobs created in
   part 2.  There are three job runners, one of which is already implemented:
     * `InThreadJobRunner` - a basic job runner that simply iterates over a list of jobs, invoking `run()` on each one in
       turn.  Note that there is no parallelism in this job runner.
     * `ThreadedJobRunner` - a multi-threaded job runner that should execute all download jobs in parallel.  The code
       in this runner will look similar to the `InThreadJobRunner`, but we will create and start java Thread objects
       for each job.  Also, you need to ensure all threads exit before the JobRunner returns from its `executeJobs` method.
       I recommend you use a [`CountdownLatch`](https://docs.oracle.com/javase/7/docs/api/java/util/concurrent/CountDownLatch.html)
       to accomplish this.
     * `ThreadPoolJobRunner` - a problem with the approach above is that it creates a thread per item that needs to be
       downloaded.  This can overwhelm the JVM with threads if you have a lot of things to be downloaded.  A more
       sophisticated approach 
       
## Tests

A test suite is provided to help you implement each of these features.  The tests can be found in the
`edu.montana.csci.csci366.archivecat.archiver` package under the `src/test/java` directory.

As usual we will be using autograder to grade the tests.

## Deploying To The Cloud

We will be deploying our applications to the cloud via [heroku](https://www.heroku.com/), a simple-to-use cloud infrastruture
provider.

## Grading

Grading is going to break up the following way:

* 70% tests
* 20% a demo of the app working on heroku
* 10% code quality

### Demo

The demo is really simple, it should just be a ~1min video of you archving the <https://montana.edu> website using your
version of ArchiveCat, deployed to heroku.  Make sure it is clear that you are running the app on your heroku account
by showing the URL you are using.

Good luck!