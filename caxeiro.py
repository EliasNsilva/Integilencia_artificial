import random
import copy


distancia = [[0, 30, 84, 56, None, None, None, 75, None, 80],
            [30, 0, 65, None, None, None, 70, None, None, 40],
            [84, 65, 0, 74, 52, 55, None, 60, 143, 48],
            [56, None, 74, 0, 135, None, None, 20, None, None],
            [None, None, 52, 135, 0, 70, None, 122, 98, 80],
            [70, None, 55, None, 70, 0, 63, None, 82, 35],
            [None, 70, None, None, None, 63, 0, None, 120, 57],
            [75, None, 135, 20, 122, None, None, 0, None, None],
            [None, None, 143, None, 98, 82, 120, None, 0, None],
            [80, 40, 48, None, 80, 35, 57, None, None, 0]]

# verifica se a cidade é valida
def nova_cd_valida(matriz, cidade_inicial, cidades, solucao):
    ct = copy.deepcopy(cidades)

    while(len(ct) > 0):
        cidade_aleatoria = ct[random.randint(0, len(ct) - 1)]

        if matriz[cidade_inicial][cidade_aleatoria] == None:
            ct.remove(cidade_aleatoria)

            if len(ct) == 0:
                return -1
        else:
            if len(ct) == 1:
                #se for a ultima cidade verifica a possibilidade de voltar pra inicial  
                if matriz[cidade_aleatoria][solucao[0]] == None:
                    return -1
            return cidade_aleatoria
    return -1

#gera uma solução aleatória 
def solucao_aleatoria(matriz):
    cidades = list(range(len(matriz)))
    solucao = []

    cidade_inicial = cidades[random.randint(0, len(cidades) - 1)]
    solucao.append(cidade_inicial)
    cidades.remove(cidade_inicial)
    i = 0

    while i < len(matriz):
        cidade_aleatoria = nova_cd_valida(matriz, cidade_inicial, cidades, solucao)
        if cidade_aleatoria == -1:
            i = 0
            cidades = list(range(len(matriz)))
            solucao = []
        else:
            solucao.append(cidade_aleatoria)
            cidades.remove(cidade_aleatoria)
            cidade_inicial = cidade_aleatoria
            i = i + 1

    solucao.append(solucao[0])
    return solucao

#gera uma nova solução a partir de uma prêvia 
def variar_solucao(matriz, solucao):
    cidade_inicial = solucao[-1]
    sol = copy.deepcopy(solucao)
    cidades = list(range(len(matriz)))
    cidades = [city for city in cidades if city not in sol]

    i = 0

    while i < len(matriz) - len(solucao):
        
        cidade_aleatoria = nova_cd_valida(matriz, cidade_inicial, cidades, sol)
        if cidade_aleatoria == -1:
            return -1
        else:
            sol.append(cidade_aleatoria)
            cidades.remove(cidade_aleatoria)
            cidade_inicial = cidade_aleatoria
            i = i + 1

    sol.append(sol[0])
    return sol

#calcula o custo da rota
def cal_custo(matriz, solucao):
    custo = 0

    for i in range(len(solucao) -2):
        custo += matriz[solucao[i]][solucao[i+1]]
    return custo

def hillClimbing(matriz):
    melhor = solucao_aleatoria(matriz)

    print(f"Solução inicial: {melhor} distância: {cal_custo(matriz, melhor)}")

    x = 0
    novo = -1
    while x < 500:
        while True:
            novo = variar_solucao(matriz, melhor[0:5])
            if novo != -1:
                break
        if cal_custo(matriz, novo) < cal_custo(matriz, melhor):
            print(f"Novo melhor: {novo} distância: {cal_custo(matriz, novo)}")
            melhor = copy.deepcopy(novo)
        x = x + 1

    print(f"Solução final: {melhor} distância: {cal_custo(matriz, melhor)}")


hillClimbing(distancia)
