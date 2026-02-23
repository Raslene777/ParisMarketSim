import csv
import random
from faker import Faker
from tqdm import tqdm
from datetime import datetime, timedelta

fake = Faker()

DATA_PATH = "C:\\Users\\rasle\\Desktop\\ServeurBoursier\\data\\"

NB_CLIENTS = 10_000
NB_INTERMEDIAIRES = 2_000
NB_COMPTES = 20_000
NB_ACTIONS = 2_000
NB_COURS = 50_000
NB_ORDRES = 100_000
NB_TRANSACTIONS = 50_000
NB_PORTF = 20_000
NB_EVENTS = 30_000

def random_datetime():
    start = datetime(2015, 1, 1)
    return start + timedelta(seconds=random.randint(0, 300000000))


print("Generating clients...")
with open(DATA_PATH + "clients.csv", "w", newline="", encoding="utf-8") as f:
    writer = csv.writer(f)
    for i in tqdm(range(1, NB_CLIENTS + 1)):
        password = str(random.randint(0, 99999)).zfill(random.randint(1, 5))
        writer.writerow([
            i,
            fake.name(),
            fake.email(),
            password,
            random_datetime(),
            random.choice(["ACTIF", "SUSPENDU"])
        ])

print("Generating accounts...")
with open(DATA_PATH + "comptes.csv", "w", newline="", encoding="utf-8") as f:
    writer = csv.writer(f)
    for i in tqdm(range(1, NB_COMPTES + 1)):
        writer.writerow([
            i,
            random.randint(1, NB_CLIENTS),
            random.randint(1, NB_INTERMEDIAIRES),
            random.randint(10_000, 1_000_000),
            random_datetime()
        ])

print("Generating actions...")
with open(DATA_PATH + "actions.csv", "w", newline="", encoding="utf-8") as f:
    writer = csv.writer(f)
    for i in tqdm(range(1, NB_ACTIONS + 1)):
        writer.writerow([
            i,
            fake.lexify(text="???").upper(),
            fake.company(),
            random.choice(["NYSE", "NASDAQ", "Euronext"]),
            random_datetime()
        ])

print("Generating price history...")
with open(DATA_PATH + "cours_actions.csv", "w", newline="", encoding="utf-8") as f:
    writer = csv.writer(f)
    for i in tqdm(range(1, NB_COURS + 1)):
        writer.writerow([
            i,
            random.randint(1, NB_ACTIONS),
            round(random.uniform(5, 1500), 2),
            random_datetime()
        ])

print("Generating orders...")
with open(DATA_PATH + "ordres.csv", "w", newline="", encoding="utf-8") as f:
    writer = csv.writer(f)
    for i in tqdm(range(1, NB_ORDRES + 1)):
        writer.writerow([
            i,
            random.randint(1, NB_COMPTES),
            random.randint(1, NB_ACTIONS),
            random.choice(["ACHAT", "VENTE"]),
            random.randint(1, 10_000),
            round(random.uniform(5, 1500), 2),
            random_datetime(),
            random.choice(["EN_ATTENTE", "EXECUTE", "ANNULE"])
        ])

print("Generating transactions...")
with open(DATA_PATH + "transactions.csv", "w", newline="", encoding="utf-8") as f:
    writer = csv.writer(f)
    for i in tqdm(range(1, NB_TRANSACTIONS + 1)):
        writer.writerow([
            i,
            random.randint(1, NB_ORDRES),
            random.randint(1, NB_ORDRES),
            random.randint(1, NB_ACTIONS),
            round(random.uniform(5, 1500), 2),
            random.randint(1, 5_000),
            random_datetime()
        ])

print("Generating portfolios...")
with open(DATA_PATH + "portefeuilles.csv", "w", newline="", encoding="utf-8") as f:
    writer = csv.writer(f)
    for i in tqdm(range(1, NB_PORTF + 1)):
        writer.writerow([
            i,
            random.randint(1, NB_COMPTES),
            random.randint(1, NB_ACTIONS),
            random.randint(1, 20_000)
        ])

print("Generating event history...")
with open(DATA_PATH + "historique_evenements.csv", "w", newline="", encoding="utf-8") as f:
    writer = csv.writer(f)
    for i in tqdm(range(1, NB_EVENTS + 1)):
        writer.writerow([
            i,
            random.choice(["ORDRE", "TRANSACTION", "COMPTE"]),
            random.randint(1, NB_ORDRES),
            fake.sentence(),
            random_datetime()
        ])

print("Massive dataset generation complete.")