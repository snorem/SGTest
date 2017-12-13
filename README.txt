For this test I generated random year values in OpenOffice Calc using the following commands:

Column A (birth year): 

RANDBETWEEN(1890;2000)

Column B (end year):

RANDBETWEEN(INDIRECT("A"&ROW());2020)