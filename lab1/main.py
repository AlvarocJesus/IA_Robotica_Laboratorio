from chatbot import ChatBot

myChatBot = ChatBot()

# Criar modelo -> Mais lento
# myChatBot.createModel()

# Apenas carregar o modelo -> Mais rapido!!!!
myChatBot.loadModel()

print('Bem vindo ao ChatBot')

pergunta = input('como posso te ajudar?')
resposta, intencao = myChatBot.chatbot_response(pergunta)
print(resposta + " [" + intencao[0]['intent'] + ']')

while (intencao[0]['intent'] != 'despedida'):
    pergunta = input('posso lhe ajudar em algo a mais?')
    resposta, intencao = myChatBot.chatbot_response(pergunta)
    print(resposta + ' [' + intencao[0]['intent'] + ']')

print('Foi um prazer atende-lo')