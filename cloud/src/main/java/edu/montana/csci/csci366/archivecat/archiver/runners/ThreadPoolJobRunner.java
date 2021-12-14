package edu.montana.csci.csci366.archivecat.archiver.runners;

import edu.montana.csci.csci366.archivecat.archiver.jobs.DownloadJob;

import java.util.List;
import java.util.concurrent.CountDownLatch;

public class ThreadPoolJobRunner implements DownloadJobRunner {
    public void executeJobs(List<? extends DownloadJob> downloadJobs) {
        // TODO implement - use a ThreadPoolExecutor with 10 threads to execute the jobs

        int count = downloadJobs.size();
        CountDownLatch latch = new CountDownLatch(count);
        for (DownloadJob downloadJob : downloadJobs) {
            var t = new Thread(new Runnable() {
                @Override
                public void run() {
                    downloadJob.run();
                    latch.countDown();
                }
            });
            t.start();
            try {
                latch.await();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
