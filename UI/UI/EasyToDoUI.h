#pragma once
#include <string>
#include <msclr/marshal_cppstd.h>
#include "Header.h"

namespace UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for EasyToDoUI
	/// </summary>
	public ref class EasyToDoUI : public System::Windows::Forms::Form
	{
	private:
		Header* head;

	public:
		EasyToDoUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			head = new Header();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EasyToDoUI()
		{
			if (components)
			{
				delete components;
				delete head;
			}
		}
	private: System::Windows::Forms::PictureBox^  displalyLogo;
	protected: 



	protected: 

	protected: 


	private: System::Windows::Forms::TextBox^  inputTextBox;
	private: System::Windows::Forms::TextBox^  outputTextBox;
	private: System::Windows::Forms::TextBox^  displayTextBox;

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(EasyToDoUI::typeid));
			this->displalyLogo = (gcnew System::Windows::Forms::PictureBox());
			this->inputTextBox = (gcnew System::Windows::Forms::TextBox());
			this->outputTextBox = (gcnew System::Windows::Forms::TextBox());
			this->displayTextBox = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->displalyLogo))->BeginInit();
			this->SuspendLayout();
			// 
			// displalyLogo
			// 
			this->displalyLogo->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"displalyLogo.Image")));
			this->displalyLogo->Location = System::Drawing::Point(1142, 76);
			this->displalyLogo->Name = L"displalyLogo";
			this->displalyLogo->Size = System::Drawing::Size(449, 200);
			this->displalyLogo->TabIndex = 4;
			this->displalyLogo->TabStop = false;
			// 
			// inputTextBox
			// 
			this->inputTextBox->BackColor = System::Drawing::Color::LavenderBlush;
			this->inputTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->inputTextBox->CausesValidation = false;
			this->inputTextBox->Location = System::Drawing::Point(91, 95);
			this->inputTextBox->Name = L"inputTextBox";
			this->inputTextBox->Size = System::Drawing::Size(976, 38);
			this->inputTextBox->TabIndex = 5;
			this->inputTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &EasyToDoUI::inputTextBox_KeyPress);
			// 
			// outputTextBox
			// 
			this->outputTextBox->BackColor = System::Drawing::Color::Gainsboro;
			this->outputTextBox->Location = System::Drawing::Point(91, 173);
			this->outputTextBox->Multiline = true;
			this->outputTextBox->Name = L"outputTextBox";
			this->outputTextBox->Size = System::Drawing::Size(976, 705);
			this->outputTextBox->TabIndex = 6;
			// 
			// displayTextBox
			// 
			this->displayTextBox->BackColor = System::Drawing::Color::Gainsboro;
			this->displayTextBox->Location = System::Drawing::Point(1120, 282);
			this->displayTextBox->Multiline = true;
			this->displayTextBox->Name = L"displayTextBox";
			this->displayTextBox->Size = System::Drawing::Size(486, 596);
			this->displayTextBox->TabIndex = 7;
			// 
			// EasyToDoUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(16, 31);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(1677, 928);
			this->Controls->Add(this->displayTextBox);
			this->Controls->Add(this->outputTextBox);
			this->Controls->Add(this->inputTextBox);
			this->Controls->Add(this->displalyLogo);
			this->Name = L"EasyToDoUI";
			this->Padding = System::Windows::Forms::Padding(20);
			this->Text = L"EasyToDoUI";
			this->Load += gcnew System::EventHandler(this, &EasyToDoUI::EasyToDoUI_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->displalyLogo))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
private: System::Void EasyToDoUI_Load(System::Object^  sender, System::EventArgs^  e) {
		 }

private: System::Void inputTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {			 
		 }

private: System::Void inputTextBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		 String ^ input;

			 input = inputTextBox->Text;
			 if (e->KeyChar == (char)13) {
				 std::string stringInput = msclr::interop::marshal_as< std::string >(input);
				inputTextBox->Text = "";

				std:: string num = head->testing(stringInput);
				String^ output = gcnew String(num.c_str());

				outputTextBox->Text =  output;
			 }
		 }
};
}
 