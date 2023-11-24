import requests
import time
import difflib
from threading import Thread
import queue


class WebsiteMonitor:
    def __init__(self):
        self.previous_content = {}
        self.threads = queue.Queue()


    def get_page_content(self, url):
        try:
            response = requests.get(url)
            response.raise_for_status()
            self.threads.put((url, response.text))
        except requests.exceptions.RequestException as e:
            print(f"Error fetching {url}: {e}")
            self.threads.put((url, None))


    def check_for_changes(self, url):
        thread = Thread(target=self.get_page_content, args=(url,))
        thread.start()


    def process_threads(self):
        while True:
            url, current_html = self.threads.get()
            if current_html is None:
                print(f"There in no content on {url}")
                return
            if url in self.previous_content:
                previous_html = self.previous_content[url]
                if previous_html != current_html:
                    self.report_changes(url, previous_html, current_html)
                else:
                    print(f"No changes on {url}")
            self.previous_content[url] = current_html


    def report_changes(self, url, previous_html, current_html):
        print(f"Changes on {url} has occured")

        output = '\n'.join(difflib.unified_diff(previous_html.splitlines(),
                                            current_html.splitlines()))
        
        text_file = open(f"{url[8:10]}.txt", "w")
        text_file.write(output)
        text_file.close()

        output2 = difflib.HtmlDiff().make_file(previous_html.splitlines(),
                                            current_html.splitlines())
        
        text_file2 = open(f"{url[8:10]}2.html", "w")
        text_file2.write(output2)
        text_file2.close()


if __name__ == "__main__":
    monitor = WebsiteMonitor()

    queue_thread = Thread(target=monitor.process_threads)
    queue_thread.start()
    while True:
        urls_to_monitor = ["https://zapisy.ii.uni.wroc.pl/", "https://skos.ii.uni.wroc.pl/my/", "https://www.wikipedia.org/"]

        for url in urls_to_monitor:
            monitor.check_for_changes(url)

        time.sleep(10)  