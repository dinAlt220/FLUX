import numpy as np
import matplotlib.pyplot as plt
from corsikaio import CorsikaFile
import sys

MASS = {"el": 0.000511, "mu": 0.10566}


map_mu = np.zeros((90, 100000))
map_el = np.zeros((90, 100000))


name = str(sys.argv[1])


with CorsikaFile(name) as f:

    for e in f:
        raw = e.data

        if raw.size == 0:
            continue


        # print(raw)
        particles = raw.reshape(-1, 7)
        encoded_ids = particles[:, 0].astype(np.int32)
        particle_ids = encoded_ids // 1000

        px = particles[:, 1].astype(np.float64)
        py = particles[:, 2].astype(np.float64)
        pz = particles[:, 3].astype(np.float64)


        for j, p in enumerate(particle_ids):

            if p == 5 or p == 6:

                #energy
                m = MASS["mu"]
                E = np.sqrt(px[j]**2 + py[j]**2 + pz[j]**2 + m*m)

                #theta
                p = np.sqrt(px[j]**2 + py[j]**2 + pz[j]**2)
                cos_theta = np.clip(pz[j] / p, -1.0, 1.0)
                theta_deg = np.degrees(np.arccos(cos_theta))

                # print(theta_deg)
                if E < 1000.0 and theta_deg < 90:
                    map_mu[int(theta_deg)][int(E*100)] = map_mu[int(theta_deg)][int(E*100)] + 1.0
            
            if p == 2 or p == 3:

                #energy
                m = MASS["el"]
                E = np.sqrt(px[j]**2 + py[j]**2 + pz[j]**2 + m*m)
    
                #theta
                p = np.sqrt(px[j]**2 + py[j]**2 + pz[j]**2)
                cos_theta = np.clip(pz[j] / p, -1.0, 1.0)
                theta_deg = np.degrees(np.arccos(cos_theta))

                # print(theta_deg)
                if E < 1000.0 and theta_deg < 90:
                    map_el[int(theta_deg)][int(E*100)] = map_el[int(theta_deg)][int(E*100)] + 1.0




with open(name + "_muons.txt", "w") as file:
    for i in range(map_mu.shape[0]):
        for j in range(map_mu.shape[1]):
            file.write("{}\t".format(map_mu[i][j]))
        file.write("\n".format(map_mu[i][j]))


with open(name + "_electrons.txt", "w") as file:
    for i in range(map_el.shape[0]):
        for j in range(map_el.shape[1]):
            file.write("{}\t".format(map_el[i][j]))
        file.write("\n".format(map_el[i][j]))


