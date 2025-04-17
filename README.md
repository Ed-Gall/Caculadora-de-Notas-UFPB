# Calculadora De Notas - UFPB

Este projeto em C é uma **calculadora acadêmica** com base no sistema de notas da UFPB. O objetivo é ajudar estudantes a entenderem sua situação nas disciplinas, oferecendo cálculos automáticos para:

- **Média da disciplina**
- **CRA (Coeficiente de Rendimento Acadêmico)**
- **Nota mínima necessária na prova final**
- **Quanto precisa tirar para ser aprovado por média (sem final)**

## 🎯 Funcionalidades

### 1. Calcular Média da Disciplina
Recebe 3 notas e calcula a média simples.

### 2. Calcular CRA
Automatiza o calculo do CRA.
![image](https://github.com/user-attachments/assets/9825bca3-122e-43eb-a7c9-2f51d21122ee)


### 3. Ver Quanto Precisa Tirar na Final
Recebe a média atual antes da final e:
- Verifica se o aluno pode fazer a final (mínimo 4.0).
- Calcula a menor nota necessária na final para passar (média final ≥ 5.0).
- Simula também o resultado se tirar 10.

### 4. Quanto Precisa Tirar para Passar por Média
Ajuda a saber o que é necessário tirar para passar direto, sem final:
- Com 1 nota: calcula a soma mínima nas próximas 2 provas.
- Com 2 notas: calcula a nota mínima na 3ª prova.
- Se for impossível, tenta simular uma **reposição da menor nota**.
- Se mesmo assim não for possível, calcula quanto seria necessário na final.

## 🖥️ Interface
O programa funciona em linha de comando e apresenta um menu interativo para o usuário escolher a opção desejada.

