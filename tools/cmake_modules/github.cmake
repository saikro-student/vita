#
# It downloads 'name' project owned by 'owner'
# from https://github.com/ and extracts it into
# "${${CMAKE_PROJECT_NAME}_3RD_PARTY_DIR}/${name}"
# direrctory.
#
# The function uses GitHub Contents API to getting
# project's archives.
#
function(fetch_3rd_party_from_github owner name)
  set(ARCHIVE_FORMAT "zipball")
  if (ARGV2)
    set(ARCHIVE_FORMAT "${ARGV2}")
  endif()

  set(BRANCH_NAME "master")
  if (ARGV3)
    set(BRANCH_NAME "${ARG3}")
  endif()

  # Construct URL using template described at
  # https://developer.github.com/v3/repos/contents/#get-archive-link.
  set(GITHUB_API_DOWNLOAD_URL
      "https://api.github.com/repos/${owner}/${name}/${ARCHIVE_FORMAT}/${BRANCH_NAME}")
  set(3RD_PARTY_DIR "${${CMAKE_PROJECT_NAME}_3RD_PARTY_DIR}")
  set(TEMP_DOWNLOAD_PATH "${3RD_PARTY_DIR}/${name}.${ARCHIVE_FORMAT}")
  file(DOWNLOAD "${GITHUB_API_DOWNLOAD_URL}" "${TEMP_DOWNLOAD_PATH}")

  # Save the contents of an archive in ARCHIVE_CONTENTS_FILE_PATH
  set(ARCHIVE_CONTENTS_FILE_PATH
      "${3RD_PARTY_DIR}/${name}.${ARCHIVE_FORMAT}.contents")
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar tfz "${TEMP_DOWNLOAD_PATH}"
                  WORKING_DIRECTORY "${3RD_PARTY_DIR}"
		  OUTPUT_FILE ${ARCHIVE_CONTENTS_FILE_PATH})
  file(STRINGS ${ARCHIVE_CONTENTS_FILE_PATH} ARCHIVE_CONTENTS)
  list(GET ARCHIVE_CONTENTS 0 ARCHIVE_ROOT_DIR_NAME)

  execute_process(COMMAND ${CMAKE_COMMAND} -E tar xfz "${TEMP_DOWNLOAD_PATH}"
                  WORKING_DIRECTORY "${3RD_PARTY_DIR}")
  file(RENAME
       "${3RD_PARTY_DIR}/${ARCHIVE_ROOT_DIR_NAME}"
       "${3RD_PARTY_DIR}/${name}")

  file(REMOVE ${TEMP_DOWNLOAD_PATH} ${ARCHIVE_CONTENTS_FILE_PATH})

endfunction()
