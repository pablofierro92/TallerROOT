import ROOT
import sys

# Abre el archivo ROOT
file = ROOT.TFile.Open("HEPData-ins2601281-v2-root.root")
if not file or file.IsZombie():
    print("Error al abrir el archivo.")
    exit()

# Obtiene el TGraph2D
graph2d = file.Get("pp_13TeV_multPtSpec/Graph2D_y1")
if not graph2d:
    print("No se encontró el TGraph2D.")
    exit()

# Listas para almacenar los datos seleccionados
y_vals = []
z_vals = []

y_errs = []
z_errs = []  

# Queremos un valor específico de x (ejemplo x_target = 1)
x_target = int(sys.argv[1])
tolerance = 1e-3  # tolerancia para considerar un punto como "cercano" a x_target

# Accede a los puntos del TGraph2D
n_points = graph2d.GetN()
for i in range(n_points):
    x = graph2d.GetX()[i]
    y = graph2d.GetY()[i]
    z = graph2d.GetZ()[i]

    ye = graph2d.GetEY()[i]    
    ze = graph2d.GetEZ()[i]    

    if abs(x - x_target) < tolerance:
        y_vals.append(float(y))
        z_vals.append(float(z))

        y_errs.append(float(ye))  
        z_errs.append(float(ze))  

# Ahora construimos un TGraphErrors
n = len(y_vals)



graph_errors = ROOT.TGraphErrors(n)
for i in range(n):
    graph_errors.SetPoint(i, y_vals[i], z_vals[i])
    graph_errors.SetPointError(i, y_errs[i], z_errs[i])  # Error en y es 0

# Graficar
c2 = ROOT.TCanvas("c2", "TGraphErrors", 1000, 800)
c2.SetLogx()
c2.SetLogy()


# Define la función de ajuste
fit_func = ROOT.TF1("fit_func", "x*[0]*(1+x/[1])^(-[2])", min(y_vals), max(y_vals))
#fit_func = ROOT.TF1("fit_func", "x*[0]+ [1]*x**2", 0, 50)
#fit_func.SetParameters(1, 1.2)
fit_func.SetParameters(1, 1.2, 8)  # Valores iniciales para los parámetros

# Opcional: poner límites razonables a los parámetros
# fit_func.SetParLimits(0, 0, 1000)
# fit_func.SetParLimits(1, 0, 100)
# fit_func.SetParLimits(2, 0, 10)

# Dibuja y ajusta
graph_errors.SetTitle(f"dN/dpT2 vs pT at mu={x_target};pT;dN/dpT2")
graph_errors.SetMarkerStyle(20)
graph_errors.Fit(fit_func, "R EX0")  # "R" = restringe al rango de la función
graph_errors.Draw("AP")

# Guardar
c2.SaveAs("fit_graph.png")


# -----> Exportar los datos
#with open("datos_exportados.dat", "w") as f:
#    f.write("# y_value  z_value  y_error  z_error\n")
#    for i in range(graph_errors.GetN()):
#        x = graph_errors.GetX()[i]
#        y = graph_errors.GetY()[i]
#        ex = graph_errors.GetErrorX(i)
#        ey = graph_errors.GetErrorY(i)
#        f.write(f"{x:.6e} {y:.6e} {ex:.6e} {ey:.6e}\n")


input("Presiona Enter para salir...")
