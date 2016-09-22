namespace std6
{

	template<class type>
	type* find(type* F,type* L,type v)
	{
		for(;F!=L; ++F)
		{
			if(*F==v)
				break;
		}
		return F;
	}

}