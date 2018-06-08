#include "pch.h"
#include "pugixml.hpp"

TEST(TestCaseName, TestGoFetch) {
	std::string categorieString = "tragedie";
	std::vector<pugi::xml_node> result;

	//choix aléatoire des questions
	std::vector<std::string> choix;
	choix.push_back("1");
	choix.push_back("2");

	//chargement du fichier
	pugi::xml_document doc;

	pugi::xml_parse_result test = doc.load_file("C:/Dev/JIN4/JIN4/Questions.xml");
	EXPECT_NE(0, test);
	pugi::xml_node questions = doc.child("document");
	pugi::xml_node categorie = questions.child(categorieString.c_str());

	// recherche des nodes des questions
	for (pugi::xml_node question = categorie.first_child(); question; question = question.next_sibling()) {

		int var = 0;
		for (pugi::xml_attribute attr = question.first_attribute(); attr; attr = attr.next_attribute())
		{
			std::string attrName = attr.name();
			std::string attrValue = attr.value();

			//ASSERT_STRNE(NULL, attrName);
			//ASSERT_STRNE(NULL, attrValue);

			for (auto i : choix) {
				if (attrName.compare("id") && attrValue.compare(i))
				{
					var++;
					result.push_back(question);
				}
			}
		}
		ASSERT_EQ(2, var);
	}
	
		
	pugi::xml_node question1 = result[0];
	pugi::xml_attribute question1attr1 = question1.first_attribute();
	pugi::xml_attribute question1attr2 = question1attr1.next_attribute();
	ASSERT_STREQ(question1attr1.value(), "1");
	ASSERT_STREQ(question1attr2.value(), "Comment se nomme la belle-mere d'Hippolyte, fils de Thesee ?");
	
	pugi::xml_node question2 = result[2];
	pugi::xml_attribute question2attr1 = question2.first_attribute();
	pugi::xml_attribute question2attr2 = question2attr1.next_attribute();
	ASSERT_STREQ(question2attr1.value(), "2");
	ASSERT_STREQ(question2attr2.value(), "Qui Antigone souhaite-t-elle donner des rites funeraires en depit de l'interdiction officielle de son oncle Creon ?");
	
}