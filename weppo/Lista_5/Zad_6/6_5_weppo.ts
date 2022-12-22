type User = {
    type: `user`;
    name: string;
    age: number;
    occupation: string;
}
type Admin = {
    type: `admin`;
    name: string;
    age: number;
    role: string;
}
export type Person = User | Admin;

export const persons: Person[] = [
    {
    type: `user`,
    name: `Jan Kowalski`,
    age: 17,
    occupation: `Student`
    },
    {
    type: `admin`,
    name: `Tomasz Malinowski`,
    age: 20,
    role: `Administrator`
    }
];
/*Do poprzedniego zadania dodano pomocnicze funkcje pełniące rolę strażników ty-
powych (choć do rozwiązania poprzedniego zadania to nie było konieczne!). W zamyśle
programisty, funkcje isAdmin i isUser miały zawęzić typ parametru funkcji logPerson,
jednak z powodu pewnego błędu w definicji tych funkcji, zamysł nie powiódł się.
Należy
 skorygować definicje typów User i Admin tak żeby zawierały dodatkowe pole, type,
zawierające informację o rodzaju obiektu (omówiony na wykładzie wzorzec unia z
wariantami!)
 dodać dodatkowe pole, z odpowiednią wartością, do przykładowych elementów w
tablicy przykładowych danych
 skorygować definicje pomocniczych funkcji isAdmin i isPerson tak żeby faktycznie
pełniły rolę strażników typowych w funkcji logPerson*/

export function isAdmin(person: Person): person is Admin {
    return person.type === `admin`;
}
export function isUser(person: Person): person is User {
    return person.type === `user`;
}
export function logPerson(person: Person) {
    let additionalInformation: string = ``;
    if (isAdmin(person)) {
        additionalInformation = person.role;
    }
    if (isUser(person)) {
        additionalInformation = person.occupation;
    }
    console.log(` - ${person.name}, ${person.age}, ${additionalInformation}`);
}

logPerson(persons[0]);
logPerson(persons[1]);