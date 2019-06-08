/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 19:43:38 by ggerardy          #+#    #+#             */
/*   Updated: 2019/05/25 19:43:38 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // todo delete
#include "asm.h"

t_string *ft_readall(char *name)
{
	/* declare a file pointer */
	FILE    *infile;
	char    *buffer;
	long    numbytes;
	t_string *res = ft_make_string(10);

/* open an existing file for reading */
	infile = fopen(name, "r");

/* quit if the file does not exist */
	if(infile == NULL)
		return 0;

/* Get the number of bytes */
	fseek(infile, 0L, SEEK_END);
	numbytes = ftell(infile);

/* reset the file position indicator to
the beginning of the file */
	fseek(infile, 0L, SEEK_SET);

/* grab sufficient memory for the
buffer to hold the text */
	buffer = (char*)calloc(numbytes, sizeof(char));

/* memory error */
	if(buffer == NULL)
		return 0;

/* copy all the text into the buffer */
	fread(buffer, sizeof(char), numbytes, infile);
	fclose(infile);

	res->data = buffer;
	res->len = numbytes;
	return (res);
}

char *ft_upd_name(char *name, char *postfix)
{
	int len = ft_strlen(name);
	name[len - 1] = '\0';
	return (ft_strjoin(name, postfix));
}

char g_names[][300] = {
		"../champion/gg.s",
		"../compiler/echo.s",
		"../compiler/fluttershy.s",
		"../compiler/gg.test.s",
		"../compiler/master_of_puppets.s",
		"../compiler/toto.s",
		"../subject/spawn.s",
		"../subject/vm_champs/champs/42.s",
		"../subject/vm_champs/champs/Backward.s",
		"../subject/vm_champs/champs/barriere.s",
		"../subject/vm_champs/champs/Car.s",
		"../subject/vm_champs/champs/championships/2014/bguy/sam_2.0.s",
		"../subject/vm_champs/champs/championships/2014/bjacob/doge.s",
		"../subject/vm_champs/champs/championships/2014/brandazz/Rainbow_dash.s",
		"../subject/vm_champs/champs/championships/2014/cdivry/youforkmytralala.s",
		"../subject/vm_champs/champs/championships/2014/clafleur/big_feet.s",
		"../subject/vm_champs/champs/championships/2014/dcohen/loose.s",
		"../subject/vm_champs/champs/championships/2014/ekocevar/mandragore.s",
		"../subject/vm_champs/champs/championships/2014/esusseli/gedeon.s",
		"../subject/vm_champs/champs/championships/2014/evlasova/terminator.s",
		"../subject/vm_champs/champs/championships/2014/fcorre/ultimate-surrender.s",
		"../subject/vm_champs/champs/championships/2014/gbir/_.s",
		"../subject/vm_champs/champs/championships/2014/gjestin/salamahenagalabadoun.s",
		"../subject/vm_champs/champs/championships/2014/gleger/Machine-gun.s",
		"../subject/vm_champs/champs/championships/2014/gmange/corelol.s",
		"../subject/vm_champs/champs/championships/2014/gpetrov/MarineKing.s",
		"../subject/vm_champs/champs/championships/2014/gudepard/Kappa.s",
		"../subject/vm_champs/champs/championships/2014/hmichals/Wall.s",
		"../subject/vm_champs/champs/championships/2014/hmoutaou/Misaka_Mikoto.s",
		"../subject/vm_champs/champs/championships/2014/kelickel/Varimathras.s",
		"../subject/vm_champs/champs/championships/2014/kmonrose/justin_bee.s",
		"../subject/vm_champs/champs/championships/2014/ldesgoui/_honeybadger.s",
		"../subject/vm_champs/champs/championships/2014/lseguin/skynet.s",
		"../subject/vm_champs/champs/championships/2014/lsirigna/live.s",
		"../subject/vm_champs/champs/championships/2014/mbacoux/meowluigi.s",
		"../subject/vm_champs/champs/championships/2014/mconraux/dubo.s",
		"../subject/vm_champs/champs/championships/2014/rabid-on/jinx.s",
		"../subject/vm_champs/champs/championships/2014/rmasse/THUNDER.s",
		"../subject/vm_champs/champs/championships/2014/sbuono/Asombra.s",
		"../subject/vm_champs/champs/championships/2014/srabah-m/littlepuppy.s",
		"../subject/vm_champs/champs/championships/2014/tdemay/champ.s",
		"../subject/vm_champs/champs/championships/2014/vrey/darksasuke.s",
		"../subject/vm_champs/champs/championships/2014/ybouvet/casimir.s",
		"../subject/vm_champs/champs/championships/2017/adenis/Explosive_Kitty.s",
		"../subject/vm_champs/champs/championships/2017/agregoir/Kittystrophic.s",
		"../subject/vm_champs/champs/championships/2017/gnebie/ultima.s",
		"../subject/vm_champs/champs/championships/2017/iburel/gateau.s",
		"../subject/vm_champs/champs/championships/2017/jaustry/mise_a_jour_windows95.s",
		"../subject/vm_champs/champs/championships/2017/nolivier/run_Kitty_RUN.s",
		"../subject/vm_champs/champs/championships/2017/pzarmehr/overwatch.s",
		"../subject/vm_champs/champs/championships/2017/tbillard/Douceur_power.s",
		"../subject/vm_champs/champs/championships/2018/arobion/kamelkaze.s",
		"../subject/vm_champs/champs/championships/2018/arobion/katchup.s",
		"../subject/vm_champs/champs/championships/2018/arobion/tchupka.s",
		"../subject/vm_champs/champs/championships/2018/bcozic/lapsang.s",
		"../subject/vm_champs/champs/championships/2018/bcozic/pai_mu_tan.s",
		"../subject/vm_champs/champs/championships/2018/bcozic/sencha.s",
		"../subject/vm_champs/champs/championships/2018/chaydont/Bazou.s",
		"../subject/vm_champs/champs/championships/2018/chaydont/Horace.s",
		"../subject/vm_champs/champs/championships/2018/chaydont/TheHarvester.s",
		"../subject/vm_champs/champs/championships/2018/mbenjell3/echo.s",
		"../subject/vm_champs/champs/championships/2018/mbenjell3/fast.s",
		"../subject/vm_champs/champs/championships/2018/mbenjell3/wave.s",
		"../subject/vm_champs/champs/championships/2018/mkamel/le_pet_de_nonne.s",
		"../subject/vm_champs/champs/championships/2018/mkamel/lou_forktologue.s",
		"../subject/vm_champs/champs/championships/2018/mkamel/master_of_puppets.s",
		"../subject/vm_champs/champs/championships/2018/nolivier/Izi_Miaou.s",
		"../subject/vm_champs/champs/championships/2018/nolivier/Kitty_Miaou.s",
		"../subject/vm_champs/champs/championships/2018/nolivier/O-Maley_Miaou.s",
		"../subject/vm_champs/champs/championships/2018/sboulet/ForgottenOne.s",
		"../subject/vm_champs/champs/championships/2018/sboulet/Hidden.s",
		"../subject/vm_champs/champs/championships/2018/sboulet/NoIdea.s",
		"../subject/vm_champs/champs/championships/2018/sgalasso3/Code_eater.s",
		"../subject/vm_champs/champs/championships/2018/sgalasso3/Eraser.s",
		"../subject/vm_champs/champs/championships/2018/sgalasso3/Stargate0_1.s",
		"../subject/vm_champs/champs/Death.s",
		"../subject/vm_champs/champs/ex.s",
		"../subject/vm_champs/champs/examples/bee_gees.s",
		"../subject/vm_champs/champs/examples/bigzork.s",
		"../subject/vm_champs/champs/examples/fluttershy.s",
		"../subject/vm_champs/champs/examples/helltrain.s",
		"../subject/vm_champs/champs/examples/turtle.s",
		"../subject/vm_champs/champs/examples/zork.s",
		"../subject/vm_champs/champs/Gagnant.s",
		"../subject/vm_champs/champs/jumper.s",
		"../subject/vm_champs/champs/lde.s",
		"../subject/vm_champs/champs/leeloo.s",
		"../subject/vm_champs/champs/mat.s",
		"../subject/vm_champs/champs/maxidef.s",
		"../subject/vm_champs/champs/mortel.s",
		"../subject/vm_champs/champs/new.s",
		"../subject/vm_champs/champs/Octobre_Rouge_V4.2.s",
		"../subject/vm_champs/champs/sebc.s",
		"../subject/vm_champs/champs/slider2.s",
		"../subject/vm_champs/champs/Survivor.s",
		"../subject/vm_champs/champs/tdc2.s",
		"../subject/vm_champs/champs/tdc3.s",
		"../subject/vm_champs/champs/tdc4.s",
		"../subject/vm_champs/champs/Torpille.s",
		"../subject/vm_champs/champs/toto.s",
  "../subject/write.s",
		"",
};

int ft_compile(char *name)
{



	t_champ	*champ;

	champ = ft_parser(name); // todo too big champ error

	ft_translate_to_bytecode(champ);

	if (champ->error_count)
		return (0);

	char *new_name = ft_upd_name(name, "cor");

	int fd = open(new_name, O_CREAT | O_TRUNC | O_WRONLY, 0666);

	write(fd, champ->res->data, champ->res->len);

	ft_free_champ(&champ, 0);

	ft_printf("compiled %s \n", name);
	return (1);
}

int main(int ac, char **av)
{
	//if (ac != 2)
	//	return (0);

	int i = 0;
	av = 0;
	ac = 0;
	while (g_names[i][0])
	{
		ft_compile(g_names[i]);
		++i;
	}



//	t_string *ref = ft_readall(new_name);
//	t_string *my = champ->res;
//	size_t i = 0;
//	while (i < my->len && i < ref->len)
//	{
//		ft_printf("Different chars ref:{Yellow}%.2x{eof} my:{Yellow}%.2x{eof} in pos %5d |%s\n",
//				  (u_char)ref->data[i], (u_char)my->data[i], i,
//			ref->data[i] == my->data[i] ?
//			"\x1B[32m+\x1B[0m" : "\x1B[1m\x1B[31m-\x1B[0m err");
//		i++;
//	}
//	if (i == ref->len)
//		ft_printf("{Red}Ref ended{eof}\n");
//	if (i == my->len)
//		ft_printf("{Red}My ended{eof}\n");



	return 0;
}