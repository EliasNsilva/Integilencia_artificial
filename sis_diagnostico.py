
class paciente:
    def __init__(self):
        self.fadiga = False
        self.cansaco = False
        self.dor_de_cabeca = False
        self.dor_no_corpo = False
        self.dor_de_garganta = False
        self.inflamacao_garganta = False
        self.tosse = False
        self.ocasional_tosse = False
        self.pulsacao_alta = False
        self.baixo_oxigenio = False
        self.perda_olfato = False
        self.perda_paladar = False
        

def KB(p1): #Base de conhecimento
    #r1
    if p1.fadiga and p1.dor_de_cabeca and p1.dor_no_corpo and p1.dor_de_garganta and p1.ocasional_tosse:
        return "COVID-19"
    #r2
    elif p1.dor_de_cabeca and p1.inflamacao_garganta and p1.tosse:
        return "Gripe"
    #r3 
    elif p1.cansaco and p1.dor_de_cabeca:
        return "Mononucleose infecciosa"
    #r4
    elif p1.cansaco and p1.inflamacao_garganta:
        return "Amigdalite"
    #r5
    elif p1.cansaco:
        return "Estresse"
    #r6
    elif p1.fadiga and p1.dor_de_cabeca and p1.pulsacao_alta and p1.baixo_oxigenio and p1.perca_olfato and p1.perca_paladar:
        return "COVID-19"

def main():
    p1 = paciente()
    print("#####################################")
    print("#####--Sistema de Diagnóstico.--#####")
    print("#####################################\n\n")
    print("Digite 1 para confirmar caso apresente o sintoma. \nDigite 0 caso não apresente.\n")

    if input("Fadiga ?  ") == '1':
        p1.fadiga = True
    if input("Cansaço ?  ") == '1':
        p1.cansaco = True
    if input("Dor de cabeça ?  ") == '1':
        p1.dor_de_cabeca = True
    if input("Dor no corpo ?  ") == '1':
        p1.dor_no_corpo = True
    if input("Ocasional dor de garganta?  ") == '1':
        p1.dor_de_garganta = True
    if input("Inflamação na garganta?  ") == '1':
        p1.inflamacao_garganta = True
    if input("Tosse?  ") == '1':
        p1.tosse = True
    if input("Tosse somente de forma ocasional?  ") == '1':
        p1.ocasional_tosse = True
    if input("Pulsação elevada?  ") == '1':
        p1.pulsacao_alta = True
    if input("Baixo nível de oxigênio?  ") == '1':
        p1.baixo_oxigenio = True
    if input("Perda de olfato?  ") == '1':
        p1.perda_olfato = True
    if input("Perda de paladar?  ") == '1':
        p1.perda_paladar = True
    
    print(f"\n\nDiagnóstico: {KB(p1)}")


main()