import requests
import time
import difflib
from threading import Thread, Lock


class WebsiteMonitor:
    def __init__(self):
        self.previous_content = {}
        self.lock = Lock()


    def get_page_content(self, url):
        try:
            response = requests.get(url)
            response.raise_for_status()
            return url, response.text
        except requests.exceptions.RequestException as e:
            print(f"Error fetching {url}: {e}")
            return url, None


    def check_for_changes(self, url):
        url, current_html = self.get_page_content(url)
        with self.lock:
            if current_html is None:
                print(f"There is no content on {url}")
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
        
        with open(f"{url[8:10]}.txt", "w") as text_file:
            text_file.write(output)

        output2 = difflib.HtmlDiff().make_file(previous_html.splitlines(),
                                            current_html.splitlines())
         
        with open(f"{url[8:10]}2.html", "w") as text_file2:
            text_file2.write(output2)

if __name__ == "__main__":
    monitor = WebsiteMonitor()

    threads = []
    while True:
        urls_to_monitor = ["https://zapisy.ii.uni.wroc.pl/", "https://skos.ii.uni.wroc.pl/my/", "https://www.wikipedia.org/"]
        for url in urls_to_monitor:
            thread = Thread(target = monitor.check_for_changes, args=(url,))
            threads.append(thread)
            thread.start()

        for thread in monitor.threads:
            thread.join()


        time.sleep(10)  
