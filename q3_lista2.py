import pandas as pd
import six
import sys
sys.modules['sklearn.externals.six'] = six

import matplotlib.pyplot as plt
from sklearn import tree
from id3 import Id3Estimator, export_graphviz
import wittgenstein as lw


data = {"historico": ["ruim", "desconhecida", "desconhecida", "desconhecida", "desconhecida", "desconhecida", "ruim", "ruim", "boa", "boa", "boa", "boa", "boa", "ruim", "boa", "ruim", "ruim", "desconhecida", "desconhecida", "desconhecida"],
        "divida": ["alta", "alta", "baixa", "baixa", "baixa", "baixa", "baixa", "baixa", "baixa", "alta", "alta", "alta", "alta", "alta", "baixa", "baixa", "baixa", "baixa", "alta", "alta"],
        "garantia": ["nenhuma", "nenhuma", "nenhuma", "nenhuma", "nenhuma", "adequada", "nenhuma", "adequada", "nenhuma", "adequada", "nenhuma", "nenhuma", "nenhuma", "nenhuma", "nenhuma", "nenhuma", "nenhuma", "adequada", "adequada", "adequada"],
        "renda": ["0 a 15k", "15k a 35k", "15k a 35k", "0 a 15k", "acima de 35k", "acima de 35k", "0 a 15k", "acima de 35k", "acima de 35k", "acima de 35k", "0 a 15k", "15k a 53k", "acima de 35k", "15k a 35k", "15k a 35k", "15k a 35k", "0 a 15k", "0 a 15k", "0 a 15k", "0 a 15k"],
        "risco": ["alto", "alto", "moderado", "alto", "baixo", "baixo", "alto", "moderado", "baixo", "baixo", "alto", "moderado", "baixo", "alto", "moderado", "moderado", "alto", "alto", "alto", "baixo"]
}

df = pd.DataFrame(data=data)
d = pd.DataFrame(data=data)

y = df.pop('risco')
X = pd.get_dummies(df) 


#ID3
estimator = Id3Estimator()
estimator.fit(X, y)

export_graphviz(estimator.tree_, "graph_id3.dot",list(X.columns))

#CART
cart = tree.DecisionTreeClassifier()
cart.fit(X,y)

tree.plot_tree(cart, feature_names=list(X.columns))
plt.show()


#RIPPER
ripper = lw.RIPPER()
ripper.fit(X, list(y), pos_class=[1,2,0])
print(ripper.out_model())

