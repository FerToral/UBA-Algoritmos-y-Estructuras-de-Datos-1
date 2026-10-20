"""Grafica mediciones CSV sin modificar los datos ni acceder a red."""
import argparse
import csv
from pathlib import Path
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
ap=argparse.ArgumentParser(description=__doc__)
ap.add_argument("csv",type=Path)
ap.add_argument("salida",type=Path)
args=ap.parse_args()
with args.csv.open(encoding="utf-8-sig",newline="") as archivo:
    filas=list(csv.DictReader(archivo))
if not filas:raise SystemExit("CSV sin datos")
fig,ax=plt.subplots(figsize=(8,4.5),layout="constrained")
for columna in [c for c in filas[0] if c.endswith("_s") or c=="segundos"]:
    for grupo in sorted({f.get("disposicion","") for f in filas}):
        datos=[f for f in filas if f.get("disposicion","")==grupo]
        ax.plot([int(f["n"]) for f in datos],[float(f[columna]) for f in datos],marker=".",label=f"{columna} {grupo}".strip())
ax.set(xlabel="Tamaño de entrada (n)",ylabel="Tiempo (segundos)",title=args.csv.stem.replace("_"," ").capitalize())
ax.grid(alpha=.2)
ax.legend(fontsize="small",frameon=False)
fig.savefig(args.salida,dpi=150)
plt.close(fig)
