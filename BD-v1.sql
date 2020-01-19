

use Gescole;


create table Gestionnaire(
	id varchar(20) primary key not null,
	nom varchar(50),
	prenom varchar(100),
	age int,
	sexe varchar(20),
	login varchar(50),
	password varchar(50),
	contact varchar(100)
	);

create table Enseignant(
	id varchar(20) primary key not null,
	nom varchar(50),
	prenom varchar(100),
	age int,
	sexe varchar(20),
	login varchar(50),
	password varchar(50),
	contact varchar(100)	
	);

	
create table Classe(
	id varchar(20) primary key not null,
	effectif int,
	libelle varchar(20)
	);
	
create table Candidature(
	id varchar(20) primary key not null,
	idClasse varchar(20),
	idProfesseur varchar(20),
	statutAccepte varchar(20),
	statutclose		varchar(20),
	FOREIGN KEY (idClasse) REFERENCES Classe(id),
	FOREIGN KEY (idProfesseur) REFERENCES Enseignant(id)
	);
	
	
create table Candidat(
	id varchar(20) primary key not null,
	nom varchar(50),
	prenom varchar(100),
	age int,
	sexe varchar(20),
	login varchar(50),
	password varchar(50),
	contact varchar(100),
	FOREIGN KEY (id) REFERENCES Candidature(id)
	);	
	
create table Matiere(
	id varchar(20) primary key not null,
	libelle varchar(50),
	idProfesseur varchar(50),
	idClasse varchar(50),
	coef int,
	FOREIGN KEY (idClasse) REFERENCES Classe(id),
	FOREIGN KEY (idProfesseur) REFERENCES Enseignant(id)	
	);
	



	
create table Eleve(
	id varchar(20) primary key not null,
	nom varchar(50),
	prenom varchar(100),
	age int,
	sexe varchar(20),
	login varchar(50),
	password varchar(50),
	idClasse varchar(20),
	contact varchar(100),
	FOREIGN KEY (idClasse) REFERENCES Classe(id)
	);


create table Bulletin(
	id varchar(20) primary key not null,
	moyenne float,
	decision varchar(100),
	idEleve varchar (20),
	rang int,
	FOREIGN KEY (idEleve) REFERENCES Eleve(id)
	);
	
create table Note(
	id varchar(20) primary key not null,
	idMatiere varchar(20),
	note float,
	coef int,
	idEleve varchar(20),
	intitule varchar(20),
	FOREIGN KEY (idMatiere) REFERENCES Matiere(id),
	FOREIGN KEY (idEleve) REFERENCES Eleve(id)
	);

	
	
	create table Cours(
	id varchar(20) primary key not null,
	idMatiere varchar(20),
	dateHeure varchar(40),
	duree int,
	FOREIGN KEY (idMatiere) REFERENCES Matiere(id)
	);
	
create table Devoir(
	id varchar(20) primary key not null,
	idMatiere varchar(20),
	dateHeure varchar(40),
	libelle varchar(40),
	duree int,
	FOREIGN KEY (idMatiere) REFERENCES Matiere(id)
	);

create table Document(
	id varchar(20) primary key not null,
	libelle varchar(40),
	url varchar(255),
	idCandidature varchar(20),
	FOREIGN KEY (idCandidature) REFERENCES Candidature(id)	
	);
	
create table Commentaire(
	id varchar(20) primary key not null,
	text text,
	dateHeure varchar(40),
	idAuteur varchar(20),
	idCandidature varchar(20),	
	FOREIGN KEY (idCandidature) REFERENCES Candidature(id)	
	);
	
insert into gestionnaire(id,nom,prenom,age,sexe,login,password,contact) 
	values ("ADMN-00001","admin","admin",25,"Homme","admin","admin","77 777 77 77");