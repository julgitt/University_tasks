def d_Hondt(election_results, mandates):
    all_votes = sum(election_results.values())
    filtered_parties = {party: votes for party, votes in election_results.items()
                        if votes * 100 >= 5 * all_votes}
    quotients = {party: 2 for party in filtered_parties}
    result = {party: 0 for party in filtered_parties}
   
    while (mandates > 0):
        party = max(filtered_parties, key=filtered_parties.get)
        result[party] += 1
        filtered_parties[party] = election_results[party] / quotients[party]
        quotients[party] += 1
        mandates -= 1
    return result
    
                

election_results = {'A': 720, 'B' : 300, 'C' : 480}
mandates_number = 8
print(d_Hondt(election_results, mandates_number))