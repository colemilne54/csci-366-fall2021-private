package edu.montana.csci.csci366.archivecat.archiver.runners;

import edu.montana.csci.csci366.archivecat.archiver.jobs.DownloadJob;

import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;

public class ThreadPoolJobRunner implements DownloadJobRunner {
    public void executeJobs(List<? extends DownloadJob> downloadJobs) {
        // TODO implement - use a ThreadPoolExecutor with 10 threads to execute the jobs

        ThreadPoolExecutor executor = (ThreadPoolExecutor) Executors.newFixedThreadPool(10);
        int count = downloadJobs.size();
        CountDownLatch latch = new CountDownLatch(count);

        for (DownloadJob downloadJob : downloadJobs) {
            executor.execute(() -> {
                downloadJob.run();
                latch.countDown();
            });
        }
        try {
            latch.await();
            System.out.println("----done----");
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

    }
}
