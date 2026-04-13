#set text(size: 11pt)
#set page(margin: 1.5cm)

= Relatório — Order Book (Sistema de Ordens de Compra e Venda)

== Introdução
A proposta do sistema é registrar e/ou executar ordens de compra e venda de uma
única ação e registrar as transações realizadas para consulta posterior, é possível
também cancelar uma ordem antes que esta tenha sido registrada.  

== Estruturas de dados utilizadas
A principal estrutura de dados utilizada para guardar as informações de ordens e transações
realizadas foi a lista encadeada. A escolha foi feita pela facilidade de implementar filas
utilizando listas encadeadas e pela eficiência de memória fornecida por ela, já que diferente
de um array dinâmico a lista encadeada reserva exatamente a quantidade de memória que está
sendo utilizada no momento. Quando garantimos o ordenamento ao inserir os dados as demais operações ficam triviais.

== Busca por contraparte
Quando uma ordem, seja de venda ou compra, passa pelo método submit é checado se a lista de ordem complementar a operação
que queremos fazer está vazia, caso contrário iteramos por essa lista e conferimos se alguma ordem presente lá cumpre com
os critérios de execução imediata, se sim a transação é executada e guardada, se não a ordem não executada é adicionada em
sua devida lista garantindo o ordenamento da fila.

== Remoção de ordens
A remoção de ordens é feita por id da ordem. Iteramos pela lista encadeada procurando pelo id da ordem que queremos deletar
e quando o achamos "costuramos" os nodes adjacentes da lista, se necessário, e apagamos a ordem e o seu node usando delete.

== Custos computacionais
Para todas as operações realizadas nas listas encadeadas (inserir, cancelar e recuperar) o custo sempre será $O(n)$, visto que
para acessarmos um item no meio da lista encadeada devemos sempre acessar o anterior, no pior caso em que o item operado
está no final da lista sempre faremos $n$ operações.
