using Zad1;

SmtpFacade smtpFacade = new SmtpFacade();

string from = "noczynska.julia@gmail.com";
string to = "noczynska.julia@gmail.com";
string subject = "Subject";
string body = "Body";
string attachmentFilePath = "path/to/attachment/file";

using (MemoryStream attachmentStream = null)
{
    smtpFacade.Send(from, to, subject, body, attachmentStream, null);
}

/*using (FileStream attachmentFileStream = File.OpenRead(attachmentFilePath))
{
    string attachmentMimeType = "application/pdf";
    smtpFacade.Send(from, to, subject, body, attachmentFileStream, attachmentMimeType);
}*/
