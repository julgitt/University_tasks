namespace CommandPattern.Receivers
{
    public class Receiver
    {
        public void DownloadFTP(string filename)
        {
            Console.WriteLine($"Pobieranie pliku przez FTP: {filename}");
        }

        public void DownloadHTTP(string url)
        {
            Console.WriteLine($"Pobieranie pliku przez HTTP: {url}");
        }

        public void CreateRandomFile(string filepath)
        {
            Console.WriteLine($"Tworzenie pliku z losową zawartością: {filepath}");
            var random = new Random();
            var buffer = new byte[1024];
            random.NextBytes(buffer);
            File.WriteAllBytes(filepath, buffer);
        }

        public void CopyFile(string src, string dest)
        {
            if (!File.Exists(src))
            {
                var random = new Random();
                var buffer = new byte[1024];
                random.NextBytes(buffer);
                File.WriteAllBytes(src, buffer);
            }
            Console.WriteLine($"Kopiowanie pliku z {src} do {dest}");
            File.Copy(src, dest, true);
        }
    }
}
