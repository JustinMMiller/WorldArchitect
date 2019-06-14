CREATE TABLE Tag (
	TagName text PRIMARY KEY,
	ScriptName text NOT NULL
);

CREATE TABLE Event (
	EventID integer PRIMARY KEY AUTOINCREMENT,
	EventTitle text,
	EventDescription text
);

CREATE TABLE Terrain (
	TagName text PRIMARY KEY,
	FOREIGN KEY (TagName) REFERENCES Tag(TagName)
);

CREATE TABLE Landmass (
	TagName text PRIMARY KEY,
	FOREIGN KEY (TagName) REFERENCES Tag(TagName)
);

CREATE TABLE Settlement (
	SettlementID integer PRIMARY KEY AUTOINCREMENT,
	SettlementName text,
	x integer NOT NULL,
	y integer NOT NULL,
);

CREATE TABLE SettlementTags (
	TagName text,
	SettlementID integer,
	PRIMARY KEY (TagName, SettlementID),
	FOREIGN KEY (TagName) REFERENCES Tag (TagName),
	FOREIGN KEY (SettlementID) REFERENCES Settlement (SettlementID)
);

CREATE TABLE SettlementEvents (
	SettlementID integer,
	EventID integer,
	DateOccured integer,
	FOREIGN KEY (SettlementID) REFERENCES Settlement (SettlementID),
	FOREIGN KEY (EventID) REFERENCES Event(EventID),
	PRIMARY KEY (SettlementID, EventID, DateOccured)
);

CREATE TABLE Parameters (
	Name text, 
	Value text,
	PRIMARY KEY (Name)
);
