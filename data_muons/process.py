import numpy as np
import matplotlib.pyplot as plt

phys = ""

MASS = {"el": 0.000511, "mu": 0.10566}

def get(name):
    energies_em = []   
    energies_mu = []

    angles_em = []
    angles_mu = [] 

    with open(name, "r") as file:
        lines = file.readlines()
        for line in lines:
            ln = line.split()

            id = float(ln[0]) // 1000

            if id == 5 or id == 6:

                px, py, pz = float(ln[1]), float(ln[2]), float(ln[3])
                m = MASS["mu"]
                E = np.sqrt(px*px + py*py + pz*pz + m*m)
                energies_mu.append(E)

                p = np.sqrt(px*px + py*py + pz*pz)
                cos_theta = np.clip(pz / p, -1.0, 1.0)
                theta_deg = np.degrees(np.arccos(cos_theta))
                angles_mu.append(theta_deg)

            if id == 2 or id == 3:

                px, py, pz = float(ln[1]), float(ln[2]), float(ln[3])
                m = MASS["el"]
                E = np.sqrt(px*px + py*py + pz*pz + m*m)
                energies_em.append(E)

                p = np.sqrt(px*px + py*py + pz*pz)
                cos_theta = np.clip(pz / p, -1.0, 1.0)
                theta_deg = np.degrees(np.arccos(cos_theta))
                angles_em.append(theta_deg)


    el_E = np.array(energies_em)
    mu_E = np.array(energies_mu)

    el_ang = np.array(angles_em)
    mu_ang = np.array(angles_mu)

    return (el_E, mu_E, el_ang, mu_ang)


el_E, mu_E, el_ang, mu_ang = get("TEST2")

cor_el_E = np.zeros(100000)
cor_mu_E = np.zeros(100)

for i in el_E:
    try:
        cor_el_E[int(i*1000)] += 1
    except:
        pass

for i in mu_E:
    try:
        cor_mu_E[round(i)] += 1
    except:
        pass






el_g4 = []
with open("../build/electron_data" + phys + ".txt", "r") as file:
    lines = file.readlines()
    for line in lines:

        if float(line.split()[0]) > 0.003:
            el_g4.append(float(line.split()[0]))

el_g4 = np.array(el_g4)



mu_g4 = []
with open("../build/muon_data" + phys + ".txt", "r") as file:
    lines = file.readlines()
    for line in lines:

        if float(line.split()[0]) > 0.4:           
            mu_g4.append(float(line.split()[0]))

mu_g4 = np.array(mu_g4)



g4_el = np.zeros(100000)
g4_mu = np.zeros(100)

for i in el_g4:
    try:
        g4_el[int(i*1000)] += 1
    except:
        pass

for i in mu_g4:
    try:
        g4_mu[round(i)] += 1
    except:
        pass






plt.title("Muon spectrum")

plt.plot(g4_mu, label=f"μ±, Geant4, " + phys + " 1 km cut")
plt.plot(cor_mu_E, label=f"μ±, CORSIKA, EPOS")

plt.xscale("log")
plt.yscale("log")

# plt.title("Muon spectrum, Cut Range = 1 m")
plt.ylabel("Number of particles")
plt.xlabel("Energy [GeV]")
plt.legend()
plt.grid(True, which="major", color="black", linestyle="-", linewidth=0.5)
plt.grid(True, which="minor", color="gray", linestyle=":", linewidth=0.5)

plt.show()



plt.title("Electrons spectrum")

plt.plot(g4_el, label=f"e±, Geant4, " + phys + " 1 km cut")
plt.plot(cor_el_E, label=f"e±, CORSIKA, EPOS")

plt.xscale("log")
plt.yscale("log")

# plt.title("Muon spectrum, Cut Range = 1 m")
plt.ylabel("Number of particles")
plt.xlabel("Energy [GeV]")
plt.legend()
plt.grid(True, which="major", color="black", linestyle="-", linewidth=0.5)
plt.grid(True, which="minor", color="gray", linestyle=":", linewidth=0.5)

plt.show()



print(len(el_g4) / len(mu_g4))
print(len(el_E) / len(mu_E))




theta_el_g4 = []
with open("../build/electron_data" + phys + ".txt", "r") as file:
    lines = file.readlines()
    for line in lines:

        if float(line.split()[0]) > 0.003:
            x = float(line.split()[1])
            y = float(line.split()[2])
            z = float(line.split()[3])

            p = np.sqrt(x*x + y*y + z*z)
            cos_theta = np.clip(-z / p, -1.0, 1.0)
            theta_deg = np.degrees(np.arccos(cos_theta))

            theta_el_g4.append(theta_deg)

theta_el_g4 = np.array(theta_el_g4)



theta_mu_g4 = []
with open("../build/muon_data" + phys + ".txt", "r") as file:
    lines = file.readlines()
    for line in lines:

        if float(line.split()[0]) > 0.4:
            x = float(line.split()[1])
            y = float(line.split()[2])
            z = float(line.split()[3])

            p = np.sqrt(x*x + y*y + z*z)
            cos_theta = np.clip(-z / p, -1.0, 1.0)
            theta_deg = np.degrees(np.arccos(cos_theta))

            theta_mu_g4.append(theta_deg)

theta_mu_g4 = np.array(theta_mu_g4)



angs_g4_el = np.zeros(90)
angs_cor_el = np.zeros(90)

for i in theta_el_g4:
    angs_g4_el[int(i)] += 1

for i in el_ang:
    angs_cor_el[int(i)] += 1



angs_g4_mu = np.zeros(90)
angs_cor_mu = np.zeros(90)

for i in theta_mu_g4:
    angs_g4_mu[int(i)] += 1

for i in mu_ang:
    angs_cor_mu[int(i)] += 1



plt.title("Muon angular distribution")


plt.plot(angs_g4_mu, label=f"μ±, Geant4, " + phys + " 1 km cut")
plt.plot(angs_cor_mu, label=f"μ±, CORSIKA, EPOS")


# plt.title("Muon spectrum, Cut Range = 1 m")
plt.ylabel("Number of particles")
plt.xlabel("Zenith angle [deg]")

# plt.xscale("log")
# plt.yscale("log")

plt.legend()
plt.grid(True, which="major", color="black", linestyle="-", linewidth=0.5)
plt.grid(True, which="minor", color="gray", linestyle=":", linewidth=0.5)

plt.show()



plt.title("Electrons angular distribution")


plt.plot(angs_g4_el, label=f"e±, Geant4, " + phys + " 1 km cut")
plt.plot(angs_cor_el, label=f"e±, CORSIKA, EPOS")


# plt.title("Muon spectrum, Cut Range = 1 m")
plt.ylabel("Number of particles")
plt.xlabel("Zenith angle [deg]")

# plt.xscale("log")
# plt.yscale("log")

plt.legend()
plt.grid(True, which="major", color="black", linestyle="-", linewidth=0.5)
plt.grid(True, which="minor", color="gray", linestyle=":", linewidth=0.5)

plt.show()