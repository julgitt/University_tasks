/*
 * Na podobieństwo poprzedniego zadania - dostarczyć takiego rozszerzenia ”oczekiwalnego” napisu, które spowoduje, że
Console.WriteLine( await "https://www.google.com" ); //
spowoduje pobranie zawartości witryny spod wskazanego adresu i zwrócenie napisu - zawartości witryny. Formalnie, chodzi o implementację metody
public static TaskAwaiter<string> GetAwaiter( this string url )
{
// uzupełnić
}
Do pobrania zawartości witryny o wskazanym adresie użyć obiektu HttpClient. Uwaga!
Użyć go poprawnie, w szczególności:
https://www.aspnetmonsters.com/2016/08/2016-08-27-httpclientwrong/
*/
using System;
using System.Runtime.CompilerServices;
using System.Net.Http;

namespace Task4List5
{
    /* 
          
                public static async Task Main(string[] args) 
                {
                    Console.WriteLine("Starting connections");
                    for(int i = 0; i<10; i++)
                    {
                        using(var client = new HttpClient())
                        {
                            var result = await client.GetAsync("http://aspnetmonsters.com");
                            Console.WriteLine(result.StatusCode);
                        }
                    }
                    Console.WriteLine("Connections done");
                }
            They are in the TIME_WAIT state which means that the connection has been closed on one side (ours) 
            but we’re still waiting to see if any additional packets come in on it 
            because they might have been delayed on the network somewhere.
            
            If we share a single instance of HttpClient then we can reduce the waste of sockets by reusing them
    */
    /*Metoda GetAwaiter tworzy obiekt HttpClient i wysyła żądanie HTTP do wskazanego adresu.
     * Jeśli żądanie zakończy się sukcesem, pobierana jest zawartość odpowiedzi w formie napisu
     * i zwracana jest przy użyciu Task.FromResult(content).GetAwaiter().
     * W przeciwnym przypadku (jeśli żądanie nie powiedzie się),
     * metoda zwraca wyjątek typu HttpRequestException z informacją o kodzie statusu odpowiedzi HTTP.
     * */
    public static class StringExtencions
    {
        private static HttpClient Client = new HttpClient();
        public static TaskAwaiter<string> GetAwaiter(this string url)
        {
            var response = Client.GetAsync(url).ConfigureAwait(false).GetAwaiter().GetResult();

            if (response.IsSuccessStatusCode)
            {
                var content = response.Content.ReadAsStringAsync().ConfigureAwait(false).GetAwaiter().GetResult();
                return Task.FromResult(content).GetAwaiter();
            }

            throw new HttpRequestException($"Request failed with status code {response.StatusCode}");
        }
    }
    class Program
    {
        public static async Task Main(string[] args)
        {
            Console.WriteLine(await "https://www.google.com");
        }
    }
}