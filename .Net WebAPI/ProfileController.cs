using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.StaticFiles;
using WebApi.DataStore;
using WebApi.Models;

namespace WebApi.Controllers
{
    [ApiController]
    public class ProfileController : ControllerBase
    {
        [HttpGet]
        [Route("GetProfile")]
        [ProducesResponseType(StatusCodes.Status200OK)]
        public IEnumerable<ProfileModel> GetProfile()
        {
            return ProfileStore.profileList;
        }

        [HttpPost]
        [Route("ResumeUpload")]
        [ProducesResponseType(StatusCodes.Status200OK)]
        public async Task<IActionResult> ResumeUpload(IFormFile file,CancellationToken cancellationToken)
        {
            var result= await File(file);
            return Ok(result);
        }
        public static async Task<string> File(IFormFile file)
        {
            string filename="";
            try
            {
                var extension="."+file.FileName.Split('.')[file.FileName.Split('.').Length-1];
                filename="resume" + extension;
                var filepath=Path.Combine(Directory.GetCurrentDirectory(),"DataStore");
                var path =Path.Combine(Directory.GetCurrentDirectory(),"DataStore",filename);
                using (var stream = new FileStream(path,FileMode.Create))
                {
                    await file.CopyToAsync(stream);
                }
            }
            catch(Exception ex)
            {
                return ex.Message;
            }
            return filename;
        }

        [HttpGet]
        [Route("DowloadResume")]
        public async Task<IActionResult> DownloadResume(string filename)
        {
            var path =Path.Combine(Directory.GetCurrentDirectory(),"DataStore",filename);
            var provider =new FileExtensionContentTypeProvider();
            if(!provider.TryGetContentType(filename, out var contentType))
            {
                contentType="application/octet-stream";
            }
            var bytes=await System.IO.File.ReadAllBytesAsync(path);
            return File(bytes, contentType, Path.GetFileName(path));

        }    
    }
}

// Created By Krishna!!!