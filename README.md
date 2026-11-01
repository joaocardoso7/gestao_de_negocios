# 🏪 Gestão de Lojas (em C)

> 🚧 **Projeto em desenvolvimento.** A primeira versão já roda no terminal, mas ainda faltam funcionalidades importantes (veja a lista abaixo).

Sistema de gestão de estoque para lojas, desenvolvido em **linguagem C**. O objetivo é praticar estruturas de dados, validação de entrada e organização de código em um problema do mundo real.

## Funcionalidades

**Concluídas**
- [x] Menu interativo no terminal
- [x] Cadastro de produtos (nome, preço e quantidade em estoque)
- [x] Listagem de produtos em formato de tabela
- [x] Validação de entrada: nome vazio, nome maior que o limite, preço e quantidade inválidos ou negativos, letras no lugar de números

**Planejadas**
- [ ] Salvar e carregar os dados em arquivo
- [ ] Remover produtos (o campo `ativo` já prepara a exclusão lógica)
- [ ] Editar produtos
- [ ] Controle de vendas e baixa de estoque
- [ ] Relatórios simples (por exemplo, produtos com estoque baixo)

## Decisões de projeto

- **Preço em centavos (`int`):** evita erros de arredondamento do `float`. O valor digitado em reais é convertido na entrada e mostrado em reais na listagem, usando divisão e resto inteiros.
- **Exclusão lógica:** cada produto tem um campo `ativo`, para que a remoção futura não exija deslocar elementos no vetor.
- **Vetor de tamanho fixo (100 produtos):** simples e suficiente para a primeira versão.
- **Tratamento do buffer de entrada:** leitura do nome com `fgets`, remoção do `\n` com `strcspn` e limpeza do buffer depois de cada `scanf`, para evitar leituras puladas.

## Como compilar e executar

```bash
gcc -Wall -Wextra -o gestao_lojas main.c
./gestao_lojas
```

## Exemplo de uso

```
=== SISTEMA DE GESTAO DE ESTOQUE ===
1. Cadastrar produto
2. Listar produtos
0. Sair
```

## Limitações conhecidas

- Os dados ficam apenas na memória e se perdem ao fechar o programa (o salvamento em arquivo é o próximo passo).
- Capacidade máxima de 100 produtos.
- Ainda não há remoção nem edição de produtos.

## Tecnologias

- Linguagem C
- GCC

## Observação

Projeto desenvolvido por mim, com orientação de IA para revisão do código e discussão das decisões de projeto.

## Autor

**João Vitor Cardoso da Silva**
Estudante de Engenharia de Software · Maringá, PR
📧 joaovitor2008cardoso@gmail.com
