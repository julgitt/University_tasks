type User = {
    typ: `user`;
    name: string;
    age: number;
    occupation: string;
}
type Admin = {
    typ: `admin`;
    name: string;
    age: number;
    role: string;
}
export type Person = User | Admin;

export const persons: Person[] = [
    {
    typ: `user`,
    name: `Jan Kowalski`,
    age: 17,
    occupation: `Student`
    },
    {
    typ: `admin`,
    name: `Tomasz Malinowski`,
    age: 20,
    role: `Administrator`
    }
];
    
function logPerson(person: Person) {
    let additionalInformation: string;
    if (person.typ == `admin`) {
        additionalInformation = person.role;
    } else {
        additionalInformation = person.occupation;
    }
    console.log(`- ${person.name}, ${person.age}, ${additionalInformation}`);
}
    /*która w takiej formie jak wyżej nie skompiluje się - na ścieżkach warunkowych dla if
    kompilator nie jest w stanie zawęzić typu parametru do jednego z dwóch podanych. Jak
    skorygować powyższy kod tak żeby poprawnie się skompilował i zadziałał?*/

logPerson(persons[0]);
logPerson(persons[1]);