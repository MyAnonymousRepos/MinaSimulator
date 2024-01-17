import json
import math
from matplotlib import pyplot as plt
from matplotlib.colors import LinearSegmentedColormap


file_path = "build/sharing.json"
figure_path = "figures/sharing.pdf"

model_name = {
    "../data/opt-125m-4.json": "OPT-125M",
    "../data/opt-350m-4.json": "OPT-350M",
    "../data/opt-1.3b-4.json": "OPT-1.3B",
    "../data/bert-base-4.json": "BERT-base",
    "../data/bert-large-4.json": "BERT-large",
    "../data/vit-base-4.json": "ViT-base",
    "../data/vit-large-4.json": "ViT-large",
}

with open(file_path, "r") as f:
    data = json.load(f)
model_list = data["model_list"]
model_list = [model_name[x] for x in model_list]
result = [[x or math.nan for x in row] for row in data["result"]]

plt.rcParams["font.family"] = "Times New Roman"
cm = LinearSegmentedColormap.from_list("my_colormap", [(255/255, 217/255, 102/255), (255/255, 242/255, 204/255), (169/255, 209/255, 142/255)], N=1000)
plt.figure(figsize=(4, 3.3))
plt.imshow(result, vmin=0.5, vmax=1.0, cmap=cm)
plt.xticks(range(len(model_list)), model_list, rotation=45)
plt.yticks(range(len(model_list)), model_list)
plt.colorbar()
for i in range(len(result)):
    for j in range(len(result[i])):
        plt.text(j, i, f"{result[i][j]:.2f}", ha="center", va="center", color="k")
plt.tight_layout(pad=0.5)
plt.savefig(figure_path, dpi=400)
