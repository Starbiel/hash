var votes = [];

function show_votes() {

    let results = {};

    for (let i = 0; i < votes.length; i++) {
        let candidateName = votes[i].name;
        if (results[candidateName]) {
            results[candidateName]++;
        } else {
            results[candidateName] = 1;
        }
    }

    for (let candidate in results) {
        console.log("Candidato " + candidate + " recebeu " + results[candidate] + " votos.");
    }

}

function vote(idPerson, namePerson) {

    if(votes.length > 0) {
        for(var i = 0; i < votes.length; i++) {
            if(votes[i].id === idPerson) {
                console.log("Erro: Eleitor já votou.");
                return;
            }
        }
    }

    votes.push({id: idPerson, name: namePerson});
    console.log("Voto registrado para " + namePerson);
    return;
}


vote(1, "João");
vote(1, "Maria");
vote(2, "Maria");
vote(3, "Maria");
vote(4, "Maria");

show_votes();


