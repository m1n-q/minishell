# export _a='ls -l'
# export _b='ls -l '
# export _c=' wc -l'
# export _d=' wc -l '

envs = [ "$a", "$b", "$c", "$d" ]

# for e1 in envs:
# 	env1 = e1
# 	for e2 in envs:
# 		env2 = e2
# 		for e3 in envs:
# 			env3 = e3
# 			for e4 in envs:
# 				env4 = e4
env1 = envs[0]
env2 = envs[1]
env3 = envs[2]
env4 = envs[3]

strings = [
	f'\"\'\'\"\"\'\'\"',
	f'\'\"\"\'\'\"\"\'',
	f'{env1}{env2}',
	f'\"{env1}\"{env2}',
	f'\'{env1}\'{env2}',
	f'{env1}\"{env2}\"',
	f'{env1}\'{env2}\'',
	f'\"{env1}\"\'{env2}\'',
	f'\"{env1}\"\"{env2}\"',
	f'\'{env1}\'\'{env2}\'',
	f'\'{env1}\'\"{env2}\"',
	f'\"{env1}{env2}\"',
	f'\'{env1}{env2}\'',
	f'\"\'{env1}\'\"',
	f'\'\"{env1}\"\'',
	f'\"\'\"{env1}\"\'\"',
	f'\'\"\'{env1}\'\"\'',
	f'\"\"\'\'{env1}\'\'\"\"',
	f'\"\"\"{env1}{env1}\"\"\"\'{env3}\'\"{env2}\"$A$P$\'$C\'',
	f'\"\"\"{env1}{env1}\"\"\"\'{env3}\'\"{env2}\"$A{env4}$\'{env4}\'',
	f'$\"$\"$\"\'\'$$\"\"\'$\'',
	f'\"$$AA\"\"\"$$AAA\"$A\"{env1}\"{env1}$A{env1}',
	f'\'$\'{env1}\'\"{env3}\"{env2}{env4}\'{env4}\'{env4}\"{env4}\"',
	f'AB\"123\"CDE',
	f'AB\"123\"{env1}{env2}CDE',
	f'AB\"123\"{env1}{env1}CDE',
	f'AB\"123\"{env2}{env4}CDE',
	f'AB\"123\"{env2}$fCDE$f$pp',
	f'$p$p{env1}{env2}{env4}{env1}',
	f'$empty {env1} $empty incs/ $empty',
	f'$empty cat $empty {env3}{env4}$P{env2}$P{env4} $empty'
]

for s in strings:
	print(s)
	print()

