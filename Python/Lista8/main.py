import asyncio
import aiohttp
from private import API_KEY


CAT_FACTS_URL = "https://meowfacts.herokuapp.com"
DAD_JOKES_URL = "https://dad-jokes.p.rapidapi.com/random/joke"
HEADERS = {
    "X-RapidAPI-Key": API_KEY,
    "X-RapidAPI-Host": "dad-jokes.p.rapidapi.com"
}


async def fetch_data(url, headers=None):
    async with aiohttp.ClientSession() as session:
        async with session.get(url, headers=headers) as response:
            try:
                response.raise_for_status() 
                return await response.json()
            except aiohttp.ClientResponseError as e:
                print(f"Error fetching data: {e}")


async def get_cat_fact():
    data = await fetch_data(CAT_FACTS_URL)
    if data:
        return data.get('data')[0]


async def get_dad_joke():
    data = await fetch_data(DAD_JOKES_URL, headers=HEADERS)
    if data:
        return data.get('body')[0].get('setup') + "\n\n...\n\n" + data.get('body')[0].get('punchline')


async def main():
    cat_fact = await get_cat_fact()
    if cat_fact:
        print(f"Random cat fact: {cat_fact}\n")

    dad_joke = await get_dad_joke()
    if dad_joke:
        print(f"Random Dad Joke: {dad_joke}\n")


if __name__ == "__main__":
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main())